#include "header.h"
#include "Thread.h"
#include "Scheduler.h"
#include "MidServer.h"
#include "Epoll.h"
#include "ListenAgent.h"
#include <pthread.h>

void* enQueue(void*);
void doRequest();
//void clean(pthread_t ,Scheduler *);

int main()
{
 Agent *midServer = MidServer::getInstance();
 pthread_t tid;
 Epoll *epoll=Epoll::getInstance();
 Agent *agent =new ListenAgent("192.168.1.253",SPORT);
// ListenAgent agent("192.168.1.253",SPORT);
if(epoll->epollRig(agent,EPOLLIN)<0)
 {
	cerr<<"rigister the epoll error"<<endl;
	return -1;
 }
 
if(epoll->epollRig(midServer,EPOLLIN)<0)
 {
	cerr<<"rigister the middle server error"<<endl;
	return -1;
 }
//cout <<"server "<<SPORT<<" is running!"<<endl;
/* 
if(pthread_create(&tid,NULL,enQueue,NULL)!=0)
 {
	cerr<<"create the producer thread error!"<<endl;
	return -1;
 }
 if(pthread_detach(tid)!=0){
 
 cerr<<"detach the tid:"<<tid<<" error"<<endl;
}
*/
//enQueue(NULL);
epoll->epollWait();
delete agent;
 return 0;
}
//发送请求至请求队列
void* enQueue(void*)
{
   cout <<"queue next"<<endl;
   Scheduler *queue = Scheduler::getInstance();
   int fd,i=1;
   cout<<"enQueue!"<<endl;
     if((fd=open("r",O_RDONLY))<0)
   {
	cerr<<"open file error"<<endl;
	return NULL;
   }
   while(i<1000)
   {
	struct req_t *req = new struct req_t;
	req->fd = fd;
	req->rid = i;
	req->req_op = _AIO_READ;
	req->data  = new char[MAXLINE+1];
	memset(req->data,'\0',MAXLINE);
	req->count=MAXLINE;
	req->status = _AIO_STATUS_SUBMIT;
	req->offset = (i-1)*MAXLINE;
	req->ret = new aio_ret_t;
	req->ret->aio_return = -1;
//	cout<<"return:"<<req->ret->aio_return<<endl;
	if(queue->request(req)<0)
	{
	cerr<<"send into the queue error!"<<endl;
	delete req;
	}
	else
	cout<<"req id:"<<req->rid<<endl;
	i++;
   }
	cout<<"finish the request !!"<<endl;
	return (void*)0;
}
//从管道中读取处理结果
void doRequest()
{
	int n;
	struct req_t *req;
	unsigned int address=0;
	MidServer* midServer = MidServer::getInstance();
	int rfd=midServer->getFd();
	while(1)
	{
	 n=read(rfd,&address,sizeof(struct req_t*));
	if(n==-1&&errno!=EINTR)
	{
	 cerr<<"read from pipe error:"<<strerror(errno)<<endl;
	}
	req = (struct req_t*)address;
	if(n==4&&req->rid!=0)
	cout <<"get result :"<<req->rid<<endl;
	delete req;
	}
	
}
