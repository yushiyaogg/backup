#include "Epoll.h"
#include "header.h"
#include "Agent.h"
#include "RequestMap.h"
#include <sys/epoll.h>

const int Epoll::m_epollsize = 1000;

Epoll::Epoll()
{
	m_pEvents = new epoll_event[m_epollsize];
	m_epollFd = epoll_create(m_epollsize);
	memset(m_pEvents,'\0',m_epollsize);
    m_pRm = RequestMap::getInstance();
}


Epoll::~Epoll()
{
	delete[] m_pEvents;
	close(m_epollFd);
}

int Epoll::epollRig(Agent* agent,const int events)
{
	struct epoll_event ev;
	bzero(&ev,sizeof(ev));
	ev.data.ptr = agent;
	ev.events = events;
	int fd = agent->getFd();
	if(-1==epoll_ctl(m_epollFd,EPOLL_CTL_ADD,fd,&ev))
	{
	 cerr<<"rigster fd "<<fd<<" into the epoll error:"<<endl;
	 return -1;
	}
	return 0;
}

int Epoll::epollMod(Agent* agent,const int events)
{
	struct epoll_event ev;

	ev.data.ptr = agent;
	ev.events = events;
	int fd = agent->getFd();
	if(-1==epoll_ctl(m_epollFd,EPOLL_CTL_MOD,fd,&ev))
	{
	 cerr<<"modify the fd "<<fd<<" error"<<endl;
	 return -1;
	}
	return 0;
}
int Epoll::epollDel(Agent* agent)
{
	struct epoll_event ev;
	int fd = agent->getFd();	
    m_pRm->clear((unsigned int)agent);
	if(-1==epoll_ctl(m_epollFd,EPOLL_CTL_DEL,fd,&ev))
	{
	 cerr<<"remove the fd  "<<fd<<" error"<<endl;
	 delete agent;
	 return -1;
	}
    delete agent;
	close(fd);
	return 0;
}

Epoll* Epoll::getInstance()
{
	static Epoll epoll;
	return &epoll;
}

void Epoll::epollWait(const int timeout)
{
	int nfds,fd;
	while(1)
	{
	 nfds = epoll_wait(m_epollFd,m_pEvents,m_epollsize,timeout);
	 if(-1==nfds&&errno==EINTR) continue;
	 else if(-1==nfds)
	 {
	  cerr<<"listen the epoll error "<<endl;
	  return;
	 } else
	 {
	   for(int i=0;i<nfds;++i)
	   {
	   Agent* agent = static_cast< Agent* >(m_pEvents[i].data.ptr);
	   if(m_pEvents[i].events&EPOLLIN)
	   {
//		cout<<"ready for read"<<endl;
		if(-1==agent->readAgent())
		{
//		  cout<<"user leave:";
		  fd = agent->getFd();
		  cout<<fd<<endl;
		  epollDel(agent);
		  close(fd);
		} 
		else
		{
//		  cout<<"epoll read agent fd:"<<agent->getFd()<<endl;
		}
	   } else if(m_pEvents[i].events&EPOLLOUT)
	   {
//		cout<<"ready for write"<<endl;
		if(-1==agent->writeAgent())
		{
//		  cout<<"user leave!"<<endl;
		  fd = agent->getFd();
		  epollDel(agent);
		  close(fd);
		}
	   }else if(m_pEvents[i].events&(EPOLLERR|EPOLLHUP))
	   {
		fd = agent->getFd();
		epollDel(agent);
		close(fd);	
	   }
	   }
	 }
//     Queue *queue=Queue::getInstance();
 //    queue->check();
	}
}
