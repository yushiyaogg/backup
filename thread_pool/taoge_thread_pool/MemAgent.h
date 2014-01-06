#ifndef _MEM_AGENT_H_
#define _MEM_AGENT_H_
#include "header.h"
#include "Agent.h"

class CBuffer;
class Scheduler;
class RequestMap;

class MemAgent:public Agent
{
public:
	MemAgent(int);
	int readAgent();
	int writeAgent();
	inline int getFd(){return m_cFd;}
	inline int setFd(int cfd){m_cFd = cfd;}
	int send(struct tagHead *);	
	void do_req(struct req_t*);
	~MemAgent();
private:
	int m_cFd;
	CBuffer *m_pBuffer;
	queue<struct tagHead*> m_pqHead;//所有的数据都缓存起来
	Scheduler* m_pqueue;
    RequestMap *m_pRm;
    static unsigned long long num;
	void dealWith(struct tagHead*);
};

#endif
