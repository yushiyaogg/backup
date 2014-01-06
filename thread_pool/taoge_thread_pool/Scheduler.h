#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_
//所有任务的下发,以及调度系统,本身也是一个线程，但是不能被睡眠,盲等锁
#include <pthread.h>
#include "header.h"
#include "Agent.h"

class Thread;
class Queue;
struct Executor
{
unsigned int pfd;
Thread *thread;
};

class Scheduler:public Agent{
public:
	static Scheduler* getInstance();
	~Scheduler();	
    int writeAgent();
    int readAgent();
    int request(struct req_t*);
    int getFd(){return m_cFd;}
    int setNonBlock(int);
private:
    int m_cFd;
	unsigned int m_now;//目前数量
	void Initial();//初始化线程，以及管道
	struct Executor *m_pExecutor;//管理线程池结果
    queue<struct req_t*> m_reqList;//请求队列
    Scheduler(unsigned int=7);
    Scheduler(const Scheduler&);
    Scheduler& operator=(const Scheduler&);
};


#endif
