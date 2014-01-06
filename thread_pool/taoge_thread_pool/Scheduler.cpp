#include "Scheduler.h"
#include "Thread.h"
#include "header.h"
#include "MidServer.h"
#include "Epoll.h"
#include <pthread.h>
#include <errno.h>
#include <sys/epoll.h>


Scheduler::Scheduler(unsigned int now)
{
	m_now = now;
	m_pExecutor = new struct Executor[m_now];
//    cout<<"Scheduler is called!"<<endl;
    Epoll*p=Epoll::getInstance();

   if(p->epollRig(this,EPOLLOUT)<0)
    {
        cerr<<"register epoll error!"<<endl;
        exit(-1);
    }
    Initial();
}
int Scheduler::readAgent(){return 0;}
Scheduler* Scheduler::getInstance()
{
       static Scheduler scheduler(13);
       return &scheduler;
}
 int Scheduler::request(struct req_t* req)
{
    m_reqList.push(req);
//    cout<<"request into queue:"<<req->rid<<endl;
    return 0;
}
int Scheduler::writeAgent()
{
    struct req_t*req;
    int n;
    while(!m_reqList.empty())
    {
        req = m_reqList.front();
  		n=write(m_cFd,&req,sizeof(struct req_t*));
		if(n!=4)
		{
            if(n==-1)
            {
                if(errno==EAGAIN||errno==EWOULDBLOCK) return 0;
                else if(errno==EINTR) continue;
                else 
                {
                    cerr<<"write into the fd error:"<<strerror(errno)<<endl;
                    getchar();
                    return -1;
                }
            }
			cerr<<"write to thread "<<" error!"<<endl;
			return 0;
		}
        else {
            m_reqList.pop();
//            cout<<"dispatch the rid:"<<req->rid<<endl;
        }
//        cout<<"request list size:"<<m_reqList.size()<<endl;
    }
    return 0;
}
//创建管道，以及线程
void Scheduler::Initial()
{
	int pipefd[2];
	struct pipeset set;
	MidServer *p = MidServer::getInstance();
    if(pipe(pipefd)!=0)
	{
     cerr<<"create pipefd error!"<<endl;
	}
    m_cFd = pipefd[1];
    setNonBlock(m_cFd);
//    setNonBlock(pipefd[0]); //用于同步目的，否则就违反原则了
    set.out = p->getWriteFd();
//	cout<<"scheduler_pipe rfd"<<pipefd[0]<<" writefd:"<<m_cFd<<endl;
    for(int i=0;i<m_now;i++)
	{
	  set.in = pipefd[0]; //线程可读的入口
	  Thread *thread = new Thread(set);
	  m_pExecutor[i].pfd = pipefd[1];//调度线程可写入口
	  m_pExecutor[i].thread = thread;
	}
}
int Scheduler::setNonBlock(int fd)
{
int flag;
if((flag=fcntl(fd,F_GETFL,0))<0)
{
    cerr<<"get file status error"<<endl;
    return -1;
}
flag |= O_NONBLOCK;
if((fcntl(fd,F_SETFL,flag))<0)
{
    cerr<<"set nonblock error"<<endl;
    return -1;
}
return 0;
}

Scheduler::~Scheduler()
{	
	Thread *thread;
	//释放m_pExecutor结构体
	for(int i=0;i<m_now;i++)
	{
	  thread = m_pExecutor[i].thread;
//	  close(m_pExecutor[i].pfd);
	  delete thread;
	}
    close(m_cFd);
	delete []m_pExecutor;
}

