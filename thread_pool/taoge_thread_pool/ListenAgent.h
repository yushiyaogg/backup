#ifndef __LISTENAGENT_H
#define __LISTENAGENT_H
#include "Agent.h"
#include "header.h"
#include <sys/epoll.h>

class Epoll;

class ListenAgent:public Agent
{
	public:
		ListenAgent(const char*,const int=SPORT);
		int readAgent();
		int writeAgent();
		int getFd();
		~ListenAgent();
	private:
		void setNonBlock(int);
		int initialServer();
		void initOption(int fd);
		struct sockaddr_in m_serverSocket;
		int m_sFd;
		Epoll *m_pEpoll;
};

#endif
