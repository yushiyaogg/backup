#include "Scheduler.h"
#include "Thread.h"
#include "header.h"
#include "MidServer.h"
#include <pthread.h>
#include <errno.h>

const unsigned int Scheduler::hash = 3;

Scheduler::Scheduler(unsigned int low,unsigned int high)
{
	m_min = low;
	m_max = high;
	m_now = low;
	m_pExecutor = new struct Executor[m_now];
//	m_pqMsg = Queue::getInstance();
}

//创建管道，以及线程
void Scheduler::Initial()
{
	int pipefd[2];
	struct pipeset set;
	MidServer *p = MidServer::getInstance();
	set.out = p->getWriteFd();
	for(int i=0;i<m_now;i++)
	{
	if(pipe(pipefd)==0)
	{
	  set.in = pipefd[0]; //线程可读的入口
//	  cout<<"set.in:"<<pipefd[0]<<endl;
	  Thread *thread = new Thread(set);
	  m_pExecutor[i].pfd = pipefd[1];//调度线程可写入口
	  m_pExecutor[i].thread = thread;
	}
	else
	{
		cerr<<"create pipefd error!"<<endl;
	}
	}
}
void Scheduler::Run()
{
	this->Initial();
}
Scheduler::~Scheduler()
{	
	Thread *thread;
	//释放m_pExecutor结构体
	for(int i=0;i<m_now;i++)
	{
	  thread = m_pExecutor[i].thread;
	  close(m_pExecutor[i].pfd);
	  delete thread;
	}
	delete []m_pExecutor;
}

void Scheduler::Schedule(struct req_t*req)
{
//	struct req_t *req;
	int fd,n;
	pthread_t tid=-1;
//	while(!(req=m_pqMsg->doRequest()))
	{
		//通过查看请求id进行转发至相关的线程
		fd = m_pExecutor[req->rid%m_now].pfd;
		tid =(m_pExecutor[req->rid%m_now].thread)->getTid();
		n=write(fd,&req,sizeof(struct req_t*));
		if(n!=4||(n==-1&&(errno!=EINTR)))
		{
			cerr<<"write to thread id:"<<tid<<" error!"<<endl;
			getchar();
		}
		else ;
//		  cout<<"write into tid:"<<tid<<endl;		
	}
}
