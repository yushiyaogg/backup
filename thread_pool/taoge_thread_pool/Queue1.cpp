#include "Queue.h"
#include "header.h"
#include "Scheduler.h"

#include <cassert>
/*
**其实这个队列根本可以不用要，因为下面是用管道来进行同步的!!
*/
Queue::Queue(){
	
	m_pmLink = new struct link;
	m_pvLink = new struct link;
	struct queue *p,*q;
	p = new struct queue;
	q = new struct queue;
	m_pmLink->head = p;
	m_pvLink->head = q;
	if(pthread_mutex_init(&m_mLink,NULL)!=0)
	{
	  cerr<<"initialize the main link mutex error!"<<endl;
	}
	if(pthread_mutex_init(&m_vLink,NULL)!=0)
	{
	  cerr<<"initialize the vice link mutex error!"<<endl;
	}
	if(!m_pmLink&&!m_pmLink->head)
	{
	 cerr<<"init the main queue error"<<endl;
	}
	initQueue(m_pmLink);
	if(!m_pvLink&&!m_pvLink->head)
	{
	 cerr<<"init the vice queue error!"<<endl;
	}
	initQueue(m_pvLink);
	scheduler = new Scheduler(7,67);
	scheduler->Run();
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
void Queue::check()
{
  if(!pthread_mutex_trylock(&m_mLink)) //获取到了主队列锁
  {
    if(!pthread_mutex_trylock(&m_vLink)) //获取了副队列锁，就可以开始合并了
    {
	combine(m_pmLink,m_pvLink);
	initQueue(m_pvLink);
	pthread_mutex_unlock(&m_vLink);
    }
	pthread_mutex_unlock(&m_mLink);
  }

}
//放入一个请求,默认为主队列，否则为副队列
int Queue::request(struct req_t*req)
{
 int flag = -1;
 if(!pthread_mutex_trylock(&m_mLink)) //获取到了主队列信号量
 {
	flag = enQueue(m_pmLink,req); //放入到了主队列
//	cout<<"req:"<<req->rid<<" into main queue!"<<endl;
	pthread_mutex_unlock(&m_mLink);
 }
 else //对不起主队列的信号量没有拿到，那就放入副队列吧
 {
   if(!pthread_mutex_trylock(&m_vLink)){
   	 flag = enQueue(m_pvLink,req);
	 if(0==flag&&0==pthread_mutex_trylock(&m_mLink)) 
		//还能放入吗，捎带放入主队列吧
	 {
	  combine(m_pmLink,m_pvLink);
	  initQueue(m_pvLink);
	  pthread_mutex_unlock(&m_mLink);	
	 }
//	 cout<<"req:"<<req->rid<<" vice queue!"<<endl;
	 pthread_mutex_unlock(&m_vLink);
  } //如果连这个都没有拿到，就任命吧阿
 }
	wakeUp();//调度者，你该工作了
 	return flag;	
}

void Queue::wakeUp()
{
  struct req_t *req=NULL;
  if(NULL!=(req=doRequest()))
  {
//      cout<<"scheduler req_t:"<<req->rid<<endl;
      scheduler->Schedule(req);
  }
}

/****从队列中取出请求
*主队列，副队列交换了
*
**/
struct req_t* Queue::doRequest()
{
  struct req_t *req =NULL;
   //先从主队列中取
    if(!pthread_mutex_trylock(&m_mLink))
   {
    deQueue(m_pmLink,req); //它看到的永远是主队列
    if(!pthread_mutex_trylock(&m_vLink)) //副队列也捎带挂上去吧
    {
	combine(m_pmLink,m_pvLink);
	initQueue(m_pvLink);
	pthread_mutex_unlock(&m_vLink);
    }
    pthread_mutex_unlock(&m_mLink);
   }
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
	destruct(m_pmLink);
	destruct(m_pvLink);
	pthread_mutex_destroy(&m_mLink);
	pthread_mutex_destroy(&m_vLink);
	delete m_pmLink->head;
	delete m_pmLink;
	delete m_pvLink->head;
	delete m_pvLink;
	delete scheduler;
}

Queue* Queue::getInstance()
{
	static Queue queue;
	return &queue;
}
