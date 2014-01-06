
#include "ListenAgent.h"
#include "MemAgent.h"
#include "Epoll.h"

ListenAgent::ListenAgent(const char* ipAddr,const int port)
{
	
	m_serverSocket.sin_family = AF_INET;
	m_serverSocket.sin_port = htons(port);
	
	if(0==inet_aton(ipAddr,&m_serverSocket.sin_addr))
	{
		cerr<<"wrong ipAddress:"<<*ipAddr<<endl;
		exit(-1);
	}
	if(initialServer()<0)
	{
	    cerr<<"initial server error has occured:"<<strerror(errno)<<endl;
		exit(-1);
	}
	m_pEpoll = Epoll::getInstance();
}

int ListenAgent::initialServer()
{

	if((m_sFd=socket(AF_INET,SOCK_STREAM,0))<0)
	{
		cerr<<"create socket error:"<<strerror(errno)<<endl;
		return -1;
	}
	setNonBlock(m_sFd);
	if(bind(m_sFd,(struct sockaddr*)&m_serverSocket,sizeof(m_serverSocket))<0)
	{
		cerr<<"bind the server error:"<<strerror(errno)<<endl;
		return -1;
	}
	if(listen(m_sFd,BACKLOG)<0) return -1;
	initOption(m_sFd);
	cout<<"server is listenning now!"<<endl;
	return 0;
}
void ListenAgent::initOption(int fd)
{
	int flag = 1;
	//设置心跳检测 端口重用
	if(setsockopt(fd,SOL_SOCKET,SO_KEEPALIVE|SO_REUSEADDR,&flag,sizeof(flag)
				)<0)
	{
	
		cerr<<"set socket option error:"<<strerror(errno)<<endl;
		return;
	}
	flag = 1;
	//设置不粘包
	if(setsockopt(fd,IPPROTO_TCP,TCP_NODELAY,&flag,sizeof(flag))<0)
	{
	 cerr<<"disable nagle error:"<<strerror(errno)<<endl;
	 return;
	}
}
void ListenAgent::setNonBlock(int fd)
{
	int flag;
	if((flag=fcntl(fd,F_GETFL,0))<0)
	{	cerr<<"set nonblock error:"<<strerror(errno)<<endl;
		return;
	}
	flag |= O_NONBLOCK;
	if(fcntl(fd,F_SETFL,flag)<0)
	{
		cerr<<"set nonblock error:"<<strerror(errno)<<endl;
		return;
	}
}

ListenAgent::~ListenAgent()
{
	close(m_sFd);
}

int ListenAgent::getFd()
{
	return m_sFd;
}

int ListenAgent::readAgent()
{
	int cfd;
	socklen_t len;
	sockaddr_in cliaddr;
	len = sizeof(cliaddr);

	while(1){
	cfd=accept(m_sFd,(struct sockaddr*)&cliaddr,&len);

	if(-1==cfd&&EINTR==errno) continue;
	else
		if(-1==cfd&&(errno!=EWOULDBLOCK&&EAGAIN!=errno)) return -1;
		else
			if(-1==cfd&&(errno==EWOULDBLOCK||errno==EAGAIN)) return 0;
			else break;
	}
	
//	cout<<"new connection "<<inet_ntoa(cliaddr.sin_addr)<<":"
//		<<ntohs(cliaddr.sin_port)<<endl;

	setNonBlock(cfd);
	initOption(cfd);
	Agent* agent = new MemAgent(cfd);
//	agent->setFd(cfd);
	m_pEpoll->epollRig(agent,EPOLLIN|EPOLLOUT);
	return 0;
}

int ListenAgent::writeAgent()
{
	return 0;

}
