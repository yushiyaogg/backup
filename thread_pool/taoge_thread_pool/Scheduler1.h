#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_
//所有任务的下发,以及调度系统,本身也是一个线程，但是不能被睡眠,盲等锁
#include <pthread.h>
#include "header.h"
#include "Agent.h"

struct req_t;
class Thread;
struct Executor
{
unsigned int pfd;
Thread *thread;
};

class Scheduler::public Agent{
public:
	Scheduler(unsigned int,unsigned int);	
	void Run();
	void Schedule(struct req_t*);//真正的调度函数
	~Scheduler();	
    int writeAgent();
    int request(struct req_t*);
    
private:
	unsigned int m_min,m_max; //线程池的最小，最大数量
	static const unsigned int hash;//利用hash进行处理
	unsigned int m_now;//目前数量
	void Initial();//初始化线程，以及管道
	struct Executor *m_pExecutor;//管理线程池结果
    
};


#endif
