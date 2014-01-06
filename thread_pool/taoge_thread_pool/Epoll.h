#ifndef _EPOLL_H_
#define _EPOLL_H_


class Agent;
class RequestMap;

class Epoll{
public:
	static Epoll* getInstance();
	int epollRig(Agent*,const int);
	int epollMod(Agent*,const int);
	int epollDel(Agent*);
	void epollWait(const int=-1);
	~Epoll();
private:	
	Epoll();
	Epoll(Epoll&);

    RequestMap *m_pRm;
	struct epoll_event* m_pEvents;
	static const int m_epollsize;
	int m_epollFd;
};

#endif
