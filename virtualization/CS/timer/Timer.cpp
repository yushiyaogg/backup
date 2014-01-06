// =====================================================================================
//
//       Filename:  Timer.cpp
//
//    Description:
//
//        Version:  1.4
//        Created:  04/03/2010 09:14:07 AM
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Peng Xuyu (Elyxier), pxy1987@gmail.com
//        Company:  NDSL UESTC
//
// =====================================================================================

#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <algorithm>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <iostream>
#include "Timer.h"
#include "../log/DevLog.h"
extern DevLog *g_pDevLog;

int
SetNonblock(int fd)
{
    int val = fcntl(fd, F_GETFL, 0);
    if (val < 0) {
        DEV_LOG(LERROR, OUT_BOTH, "SetNonblock::fcntl");
        return TIMER_FAIL;
    }
    if ((val = fcntl(fd, F_SETFL, val | O_NONBLOCK)) < 0) {
        DEV_LOG(LERROR, OUT_BOTH, "SetNonblock::fcntl");
        return TIMER_FAIL;
    }
    return TIMER_SUCCESS;
}


void
TimerSigAlrm(int signo)             //operated only by Timer Thread
{
    g_TimerManager.checkTimeOut();
}

void*
TimerThread(void* arg)
{
    sigset_t      set;
    Timer*        p;
    struct itimerval    val;

    if (sigemptyset(&set) || sigaddset(&set,SIGALRM))
    {
        pthread_exit((void*)0);
    }
    while (pthread_sigmask(SIG_UNBLOCK,&set,NULL) < 0) {}

    val.it_value.tv_sec = 1;
    val.it_value.tv_usec=0;
    val.it_interval.tv_sec=1;
    val.it_interval.tv_usec=0;

    while (setitimer(ITIMER_REAL,&val,NULL) < 0) {}


    //timermanager loops to read Timer objs from message queue 1,and treat the clock events
    for (;;)
    {
        //TimerManager reads message queue 1
        p=g_TimerManager.recvTimer();
        if (p == NULL)
        {
            continue;
        }
        else
        {
            if (g_TimerManager.insertTimer(p) == TIMER_1ST_POS)
            {
                g_TimerManager.checkTimeOut();
            }
        }
    }
}




//========================== Timer ========================================================




//constructor
Timer::Timer(unsigned int mtime,long pri=1) :
        m_bDetached(false),
        m_bDone(false),
        m_Changing(0),
        m_Tid(pthread_self()),
        m_Pri(pri),
        m_TimeOutLen(mtime),
        m_ExpiredTime(mtime + (unsigned int)(time(NULL)))
{
}

Timer::Timer(void) :
        m_bDetached(false),
        m_bDone(false),
        m_Changing(0),
        m_Tid(pthread_self()),
        m_Pri(100),
        m_TimeOutLen(1000000000),
        m_ExpiredTime(1000000000)
{
}


//insert the timer obj into message queue 1
int
Timer::attachTimer(Epoll* epoll)
{
    m_bDone=false;
    m_bDetached=false;
    if (TIMER_FAIL == g_TimerManager.registerThread(pthread_self(),epoll))
    {
        DEV_LOG(LERROR, OUT_BOTH, "Timer::attackTimer:registerThread error.");
        return FAILED;
    }
    g_TimerManager.MTSendTimer(this,TIMER_CMD_ADD);
    return TIMER_SUCCESS;
}

//remove the timer obj from message queue 1
int
Timer::detachTimer(void)
{
    if (m_bDone)
    {
        delete this;
        return SUCCESSFUL;
    }
    m_bDetached = true;
    g_TimerManager.MTSendTimer(this,TIMER_CMD_DEL);
    return SUCCESSFUL;
}

bool
Timer::detached()
{
    return m_bDetached;
}

int
Timer::changing()
{
    return m_Changing;
}

void
Timer::cancelChange()
{
    --m_Changing;
}

int
Timer::updateExpiredTime(unsigned int newLen)
{
    m_ExpiredTime = newLen + (unsigned int)(time(NULL));
    if (!m_bDone)
    {
        ++m_Changing;
        g_TimerManager.MTSendTimer(this,TIMER_CMD_CHANGE);

    }
    else
    {
        m_bDone=false;
        g_TimerManager.MTSendTimer(this,TIMER_CMD_ADD);
    }
    return TIMER_SUCCESS;
}

//get the expiredtime of the Timer obj
unsigned int
Timer::getExpiredTime()
{
    return m_ExpiredTime;
}

//set the expiredtime of the Timer obj
int
Timer::setExpiredTime(unsigned int len)
{
    m_ExpiredTime = len + (unsigned int)time(NULL);
    m_TimeOutLen = len;
    return 1;
}

//get the Timer object's priority
long
Timer::getPriority()
{
    return m_Pri;
}

//set the Timer object's priority
void
Timer::setPriority(long pri)
{
    m_Pri=pri;
}

//get the process ID of the Timer obj
pthread_t
Timer::getTid()
{
    return m_Tid;
}





//======================== TimerManager  ==========================================================




//constructor
TimerManager::TimerManager()
{
    while (pipe(m_MsgPipe1) < 0) {}
}

//destructor
TimerManager::~TimerManager()
{
    std::map<pthread_t,int>::iterator mapIt;
    std::multiset<Timer*>::iterator   it;

    for (it = m_TimerList.begin(); it != m_TimerList.end(); ++it)
    {
        delete (*it);
    }
    m_TimerList.clear();

    close(m_MsgPipe1[0]);
    close(m_MsgPipe1[1]);

    for (mapIt = m_MsgRPipeList.begin(); mapIt != m_MsgRPipeList.end(); ++mapIt)
    {
        close(mapIt->second);
    }
    m_MsgRPipeList.clear();
    for (mapIt = m_MsgWPipeList.begin(); mapIt != m_MsgWPipeList.end(); ++mapIt)
    {
        close(mapIt->second);
    }
    m_MsgWPipeList.clear();
}

//register thread in TimerManager, which will allocate a pipe for back sending if it's not registered yet
int
TimerManager::registerThread(pthread_t tid,Epoll* epoll)
{
    int p[2];

    if ( !(m_MsgRPipeList.count(tid) == 0 && m_MsgRPipeList.count(pthread_self()) == 0))
    {
        return TIMER_SUCCESS;
    }
    if (pipe(p) < 0)
    {
        DEV_LOG(LERROR, OUT_BOTH, "TimerManager::registerThread::pipe");
        return TIMER_FAIL;
    }
    if (FAILED == SetNonblock(p[0]))
    {
        DEV_LOG(LERROR, OUT_BOTH, "TimerManager::registerThread failed.");
        return FAILED;
    }
    m_MsgRPipeList[tid] = p[0];
    m_MsgWPipeList[tid] = p[1];

    m_EpollEvent.setEpoll(epoll);
    m_EpollEvent.setFd(p[0]);
    m_EpollEvent.setHandler(this);
    if (FAILED == m_EpollEvent.registerREvent())
    {
        DEV_LOG(LERROR, OUT_BOTH, "TimerManager::registerThread failed.");
        return FAILED;
    }

    return TIMER_SUCCESS;
}

//initialize TimerManager
int
TimerManager::init()
{
    pthread_t    tid = 0;
    struct sigaction act;
    sigset_t             theSet;
    int ret = 0;

    ret = sigemptyset(&theSet);
    ret = sigaddset(&theSet,SIGALRM);
    ret = ret;
    if (sigprocmask(SIG_BLOCK,&theSet,NULL) < 0)
    {
        DEV_LOG(LERROR, OUT_BOTH, "TimerManager::Init:sigprocmask");
        return TIMER_FAIL;
    }

    bzero(&act,sizeof(act));
    ret = sigemptyset(&(act.sa_mask));
    act.sa_handler=TimerSigAlrm;
    if (sigaction(SIGALRM,&act,NULL) < 0)
    {
        DEV_LOG(LERROR, OUT_BOTH, "TimerManager::Init::sigaction");
        return TIMER_FAIL;
    }

    if (SUCCESSFUL != pthread_create(&tid,NULL,TimerThread,NULL))
    {
        DEV_LOG(LERROR, OUT_BOTH, "TimerManager::init:pthread_create error.");
        return FAILED;
    }
    return TIMER_SUCCESS;
}

//insert a Timer obj into the timerlist
int
TimerManager::insertTimer(Timer *p)
{
    blockSIGALRM();
    m_TimerList.insert(p);
    if (*(m_TimerList.begin()) == p)
    {
        unblockSIGALRM();
        return TIMER_1ST_POS;
    }
    else
    {
        unblockSIGALRM();
        return TIMER_NOT_1ST_POS;
    }
}

//remove a Timer obj from the timerlist
int
TimerManager::removeTimer(Timer *p)
{
    multiset<Timer*, LessTimer>::iterator it;

    blockSIGALRM();
    it = m_TimerList.begin();
    while (it != m_TimerList.end())
    {
        if (*it == p)
        {
            m_TimerList.erase(it);
            unblockSIGALRM();
            return TIMER_FOUND;
        }
        ++it;
    }
    unblockSIGALRM();
    return TIMER_NOT_FOUND;
}

//check whether any timer is timeout.and execute function doAction() if it's expired
void
TimerManager::checkTimeOut(void)
{
    int ret = 0;
    unsigned int Tm = (unsigned int)time(NULL);
    map<pthread_t ,multiset<Timer*,LessPri> > l_TidList;
    multiset<Timer*,LessPri> l_ExpiredTimerList;
    map<pthread_t ,multiset<Timer*,LessPri> >::iterator listit;
    multiset<Timer*,LessPri>::iterator setit;                         //iterator for traversing
    multiset<Timer*,LessTimer>::iterator it = m_TimerList.begin();    //iterator for traversing the timer list m_TimerList

    if (getLength() <= 0)
    {
        return;
    }

    //if it is timeout,erase the timer from the timerlist and alert the main thread,then send it back
    while ((it != m_TimerList.end()) &&  (*it)->getExpiredTime() <= Tm)
    {
        l_TidList[(*it) -> getTid()].insert(*it);
        m_TimerList.erase(it);
        it = m_TimerList.begin();
        Tm = (unsigned int)time(NULL);
    }
    for (listit = l_TidList.begin() ; listit != l_TidList.end() ; ++listit)
    {
        for (setit = (listit->second).begin() ; setit != (listit->second).end() ; ++setit)
        {
            ret = sendTimer(*setit);
        }
    }

    ret = ret;
    return;
}





//TimerManager reads one Timer from main thread through message queue 1
Timer*
TimerManager::recvTimer()
{
    size_t           n;
    int              result;
    Timer*           p;
    TimerMsg_t       theMsg;
    int              ret = 0;

    result = -1;
    bzero(&theMsg,sizeof(TimerMsg_t));
    for (;;)                                                    //loop until msg is read successfully
    {
        n=read(m_MsgPipe1[0],&theMsg,sizeof(TimerMsg_t));
        if (n < 0)
        {
            if (errno == EINTR)
            {
                continue;
            }
            else
            {
                DEV_LOG(LERROR, OUT_BOTH, "TimerManager::recvTimer::read");
                continue;
            }
        }
        else
        {
            if (n != sizeof(TimerMsg_t))
            {
                return NULL;
            }
            break;
        }
    }

    p=(Timer*)(theMsg.ptr);
    if (theMsg.cmd == TIMER_CMD_DEL)                                //a deleting message
    {
        if (removeTimer(p) == TIMER_FOUND)                        //the obj's in TimerList
        {
            checkTimeOut();
            ret = sendTimer(p);                                         //send it back to MT
        }
        return NULL;
    }
    else if (theMsg.cmd == TIMER_CMD_CHANGE)
    {
        if (removeTimer(p) == TIMER_FOUND)
        {
            p->cancelChange();
            result = insertTimer(p);
        }
        else
        {
            result = insertTimer(p);
        }
        if (result == TIMER_1ST_POS)
        {
            checkTimeOut();
        }
        return NULL;
    }
    ret = ret;
    return p;
}

//TimerManager sends one expired Timer to main thread through message queue 2
int
TimerManager::sendTimer(Timer *p)
{
    TimerMsg_t         theMsg;

    bzero(&theMsg,sizeof(TimerMsg_t));
    theMsg.mpri=p->getPriority();
    theMsg.ptr=p;
    theMsg.cmd=TIMER_CMD_NULL;
    for (;;)
    {
        if (write(m_MsgWPipeList[p->getTid()],(const void*)&theMsg,sizeof(TimerMsg_t)) < 0)
        {
            if (errno == EINTR)
            {
                continue;
            }
            else
            {
                DEV_LOG(LERROR, OUT_BOTH, "TimerManager::sendTimer:write");
                return TIMER_FAIL;
            }
        }
        else
        {
            break;
        }
    }
    return TIMER_SUCCESS;
}


//main thread reads one expired Timer from message queue 2
Timer*
TimerManager::MTRecvTimer()
{
    int        nbytes;
    Timer*     p;
    TimerMsg_t theMsg;

    bzero(&theMsg,sizeof(TimerMsg_t));
    for (;;)
    {
        nbytes=read(m_MsgRPipeList[pthread_self()],&theMsg,sizeof(TimerMsg_t));
        if (nbytes < 0)
        {
            if (errno == EINTR)
            {
                continue;
            }
            else if (errno == EAGAIN)
            {
                return NULL;
            }
            else
            {
                DEV_LOG(LERROR, OUT_BOTH, "TimerManager::MTRecvTimer:read");
                return NULL;
            }
        }
        else
        {
            if ((size_t)nbytes != sizeof(TimerMsg_t))
            {
                continue;
            }
            break;
        }
    }
    p=(Timer*)(theMsg.ptr);
    return p;
}

//main thread sends one Timer to TimerManager through message queue 1
void
TimerManager::MTSendTimer(Timer *p,int cmd = TIMER_CMD_ADD)
{
    TimerMsg_t theMsg;
    int n;

    bzero(&theMsg,sizeof(TimerMsg_t));
    theMsg.mpri=p->getPriority();
    theMsg.cmd=cmd;
    theMsg.ptr=p;

    for (;;)
    {
        n = write(m_MsgPipe1[1],(const void*)&theMsg,sizeof(TimerMsg_t));
        if (n < 0)
        {
            if (errno == EINTR)
            {
                continue;
            }
            else
            {
                DEV_LOG(LERROR, OUT_BOTH, "TimerManager::MTSendTimer:write");
                continue;
            }
        }


        else
        {
            break;
        }
    }
}

int
TimerManager::getLength()
{
    return m_TimerList.size();
}

int
TimerManager::recvData()
{
    Timer *p;
    while (true)
    {
        p = g_TimerManager.MTRecvTimer();
        if (p == NULL) {
            break;
        }
        if (p->changing()) {
            p->cancelChange();
            continue;
        }
        if (p->detached()) {
            delete p;
            continue;
        }

        p->setDone();
        if (FAILED == p->doAction())
        {
            DEV_LOG(LERROR, OUT_BOTH, "Timer::doAction error.");
            return SUCCESSFUL;
        }
    }

    return SUCCESSFUL; // ?? niexw
}

bool
Timer::isDone()
{
    return m_bDone;
}

void Timer::setDone()
{
    m_bDone = true;
}

void
TimerManager :: blockSIGALRM(void)
{
    sigset_t             theSet;
    int ret = 0;

    ret = sigemptyset(&theSet);
    ret = sigaddset(&theSet,SIGALRM);
    ret = ret;
    if (pthread_sigmask(SIG_BLOCK,&theSet,NULL) < 0)
    {
        DEV_LOG_ERROR("pthread_sigmask error");
    }
}

void
TimerManager :: unblockSIGALRM(void)
{
    sigset_t             theSet;
    int ret = 0;

    ret = sigemptyset(&theSet);
    ret = sigaddset(&theSet,SIGALRM);
    ret = ret;
    if (pthread_sigmask(SIG_UNBLOCK,&theSet,NULL) < 0)
    {
        DEV_LOG_ERROR("pthread_sigmask error");
    }
}

