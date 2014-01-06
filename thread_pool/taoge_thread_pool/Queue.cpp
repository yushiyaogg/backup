#include "Queue.h"
#include "header.h"

#include <cassert>
/*
**其实这个队列根本可以不用要，因为下面是用管道来进行同步的!!
*/
Queue::Queue(){
	
	m_pLink = new struct link;
	struct queue *p;
	p = new struct queue;
	m_pLink->head = p;
	if(!m_pLink&&!m_pLink->head)
	{
	 cerr<<"init the vice queue error!"<<endl;
	 return;
	}
	initQueue(m_pLink);
}

void inline Queue::initQueue(struct link*list)
{
	list->head->req = NULL;
	list->head->next = NULL;
	list->tail = list->head;	
}

int Queue::enQueue(struct link*list,struct req_t*req)
{
	struct queue *p = new struct queue;
	if(!p) return -1;
	p->req = req;
	p->next = NULL;
	list->tail->next = p;
	list->tail = p;
	return 0;
}

//将list2挂载到list1,只需要锁住list1
int Queue::combine(struct link* &list1,struct link* &list2)
{
	struct link *p,*q;
	struct queue *p1,*q1;
	if(isEmpty(list1)) //list1为空，直接交换两指针
	{
	  p = list1;
	  list1 = list2;
	  list2 = p;
	}
	else if(!isEmpty(list2))//list2不为空,直接链接
	{ 
	  p1 = list2->head->next;
          q1 = list2->tail;
	  list1->tail->next = p1;
	  list1->tail = q1;
//	  initQueue(list2); //让被调用者去实现，否则两个信号量同时获取不好吧
	}
	  return 0;
}
//放入一个请求,默认为主队列，否则为副队列
int Queue::request(struct req_t*req)
{
 	return  enQueue(m_pLink,req);
}


/****从队列中取出请求
*主队列，副队列交换了
*
**/
struct req_t* Queue::doRequest()
{
   struct req_t *req =NULL;
   //先从主队列中取
    deQueue(m_pLink,req); //它看到的永远是主队列
    return req;
}
int Queue::deQueue(struct link* list,struct req_t *&req)
{
	struct queue *p;
	if(isEmpty(list)) return -1;
	if(list->head->next == list->tail)
	{
	  p = list->head->next;
	  list->head->next = NULL;
	  list->tail = list->head;
	} 
	else
	{
	  p = list->head->next;
	  list->head->next = p->next;
	}
	req = p->req;
	delete p;
	return 0;
}

void Queue::destruct(struct link* list)
{
	struct req_t *req;
	while(!isEmpty(list))
	{
	  deQueue(list,req);
	  delete[] req->data;
      delete req->ret;
      delete req;
	}
}

Queue::~Queue()
{
	destruct(m_pLink);
	delete m_pLink->head;
	delete m_pLink;
}

Queue* Queue::getInstance()
{
	static Queue queue;
	return &queue;
}
