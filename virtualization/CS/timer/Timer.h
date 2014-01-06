#ifndef _TIMER_H
#define _TIMER_H

#include <map>
#include <set>
#include <sys/types.h>
#include <sys/epoll.h>
#include "../comm/Agent.h"
#include "../comm/EpollEvent.h"
#include "../comm/Error.h"
using namespace std;

#define    TIMER_MSG_SIZE       20
#define    TIMER_SUCCESS        SUCCESSFUL
#define    TIMER_FAIL           FAILED
#define    TIMER_CMD_ADD        1
#define    TIMER_CMD_DEL        2
#define    TIMER_CMD_CHANGE     3
#define    TIMER_CMD_NULL       0
#define    TIMER_FILEPATH       "./"
#define    TIMER_1ST_POS        1
#define    TIMER_NOT_1ST_POS    0
#define    TIMER_FOUND          1
#define    TIMER_NOT_FOUND      0
#define    TIMER_MAXPIPES       100

class Timer
{
    friend class TimerManager;
public:
    Timer(void);
    Timer(unsigned int, long);
    virtual int     doAction(void) {
        return SUCCESSFUL;
    }
    virtual int     updateExpiredTime(unsigned int);
    int             attachTimer(Epoll*);
    int             detachTimer(void);
    unsigned int    getExpiredTime();
    int             setExpiredTime(unsigned int);
    long            getPriority();
    void            setPriority(long);
    pthread_t       getTid();
    bool            detached(void);
    int             changing(void);
    void            cancelChange();
    bool            isDone();
    void            setDone();

protected:
    virtual         ~Timer() {}

private:
    bool            m_bDetached;          //whether this Timers obj has been detached
    bool            m_bDone;
    int             m_Changing;
    pthread_t       m_Tid;               //the thread id of the thread that created this Timer obj
    long            m_Pri;               //the priority
    unsigned int    m_TimeOutLen;        //time out length
    unsigned int    m_ExpiredTime;       //timer will be expired at this ime
};

//the rule for sorting of multiset
struct LessTimer : public std::binary_function<Timer*,Timer*,bool>
{
    bool operator()( Timer* leftVal, Timer* rightVal) const
    {
        return ( leftVal->getExpiredTime() < rightVal->getExpiredTime() );
    }
};

struct LessPri : public std::binary_function<Timer*,Timer*,bool>
{
    bool operator()( Timer* leftVal, Timer* rightVal) const
    {
        return ( leftVal->getPriority() < rightVal->getPriority() );
    }
};


class TimerManager : public Agent
{
public:
    TimerManager();
    virtual ~TimerManager();
    int        init();                   //initialize the TimerThread
    int        registerThread(pthread_t,Epoll*);          //
    int        removeTimer(Timer*);      //remove the address of a Timer obj from m_TimerList
    int        insertTimer(Timer*);      //insert the address of a Timer obj from m_TimerList
    void       checkTimeOut(void);       //check m_TimerList and remove all timed out members
    Timer*     recvTimer();          //TimerManager reads message queue 1
    int        sendTimer(Timer*);        //TimerManager writes message queue 2
    Timer*     MTRecvTimer();        //main thread read message queue 2
    void       MTSendTimer(Timer*,int);  //main thread write message queue 1
    int        getLength();              //return the length of m_TimerList
    int        recvData();
    int        sendData() {
        return SUCCESSFUL;
    }

private:
    int        m_MsgPipe1[2];            //for TimerManager receiving Timers from main thread

    EpollEvent m_EpollEvent;
    std::map<pthread_t,int> m_MsgRPipeList;
    std::map<pthread_t,int> m_MsgWPipeList;
    std::multiset<Timer*,LessTimer> m_TimerList;

    void blockSIGALRM(void);
    void unblockSIGALRM(void);
};

//the format of data structure that be sent and received in the tow Message Queues
typedef struct
{
    long       mpri;            //priority of Timer obj
    Timer*     ptr;
    int        cmd;
}TimerMsg_t;


extern TimerManager g_TimerManager;

#endif
