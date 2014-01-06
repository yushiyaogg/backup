#ifndef _QUEUE_H_
#define _QUEUE_H_
#include <pthread.h>
//当队列进入了数据之后，就直接通知下面的调度者进行通知，避免了用一个线程运转
class Scheduler;
struct req_t;
//单件模式，上面的请求通过队列进行转发到下面
class Queue{
public:
	static Queue* getInstance();
	int request(struct req_t*);
	struct req_t* doRequest();
	bool isEmpty();
	void check();//用于epollwait调用
	~Queue();
private:
	struct queue
	{	
	  struct queue *next;
	  struct req_t *req;
	};
	struct link //队列元素项
	{
	 struct queue *head;
	 struct queue *tail;
	};
	struct link *m_pmLink,*m_pvLink;//两条队列实现
	pthread_mutex_t m_mLink,m_vLink;//每条队列一个信号量
	int enQueue(struct link*,struct req_t*);
	int deQueue(struct link*,struct req_t*&);
	void wakeUp();//通知调度者取取请求了
	bool isEmpty(struct link* list){return list->head==list->tail;}
	void destruct(struct link*);
	void inline initQueue(struct link *list);
	int combine(struct link*&,struct link*&);
	Scheduler *scheduler;
	Queue();
	Queue& operator=(Queue&);
	Queue(const Queue&);

};
#endif
