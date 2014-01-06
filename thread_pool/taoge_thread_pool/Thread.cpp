#include "header.h"
#include <pthread.h>
#include <sys/file.h>
#include "Thread.h"
#include <fstream>
#include "aio.h"

//ofstream out("thread");
unsigned long Thread::num = 1;

Thread::Thread(struct pipeset _fdset)
{
	set.in = _fdset.in; //可读部分
	set.out = _fdset.out;	//写入部分
	int err=pthread_create(&tid,NULL,Execute,(void*)this);
	if(err!=0)
	{
	  cerr<<"create thread error!"<<endl;
	  return;
	}
	//将自己生成的线程自动取消
	if(0!=pthread_detach(tid))
	{
	 cerr<<"detach worker thread "<<tid<<" error"<<endl;
	}
}
void Thread::setNonBlock(int fd)
{
    int flag;
    if((flag=fcntl(fd,F_GETFL,0))<0)
    {
        cerr<<"set nonblocking error!"<<endl;
        return;
    }
    flag |= O_NONBLOCK;
    if(fcntl(fd,F_SETFL,flag)<0)
    {
        cerr<<"set nonblock error!"<<endl;
        return;
    }
}

Thread::~Thread()
{
	close(set.in);
}
//SIGPIPE信号write to pipe with no readers
int Thread::Execute()
{
	int rfd,wfd;
	rfd = set.in;
	wfd = set.out;
	int i,j;
	struct req_t *req;
	unsigned int address=0;
	while(1) 
	{
	 i=read(rfd,&address,sizeof(struct req_t*));
    if(i==-1&&(errno==EINTR||errno==EAGAIN||errno==EWOULDBLOCK)) continue;
    else if(i==-1)
    {	
        cerr<<"read from pipe error:"<<strerror(errno)<<endl;
        getchar();
        return -1;
	}
	req = (struct req_t*)address;
    dealWith(req);
    //防止把数据写入管道阻塞
    m_vAddr.push_back(address);
    for(vector<unsigned int>::iterator it=m_vAddr.begin();it<m_vAddr.end();it++)
    {
     address=*it;
    j= write(wfd,&address,sizeof(struct req_t*)); 
     if(j==-1) 
	  { 
        if(errno==EINTR) continue;
        else if(errno==EAGAIN||errno==EWOULDBLOCK) break;
        else
        {
		cerr<<"write into pipe error!"<<endl;
		getchar();
        return -1;
        }
	  }
      else if(j!=4)
	  {
		cerr<<"write into pipe error:"<<strerror(errno)<<endl;
		getchar();
        return -1;
	  } 
     else
      {
//        cout<<"write it:"<<*it<<endl;
        m_vAddr.erase(it);
        num++;
      }
    }
//    cut<<"size:"<<m_vAddr.size()<<endl;
//      out<<"size:"<<m_vAddr.size()<<" tid:"<<pthread_self()<<" response num:"<<num<<endl;
	}
	return 0;
}
//处理操作命令
void Thread::dealWith(struct req_t* req)
{
	int flag;
	off_t offset;
	if(_AIO_CANCEL==req->req_op) return;
	offset = req->offset;
	if(offset<0)
	{
	  if(flock(req->fd,LOCK_EX)<0)
	  {
		req->ret->aio_return = -1;
		req->ret->aio_errno = errno;
		return;
	  }
	  offset = lseek(req->fd,0,SEEK_CUR);
	  flock(req->fd,LOCK_UN);
	}
	switch(req->req_op)
	{
	  case _AIO_READ: 
		flag=aio_read(req->fd,req->data,req->count,offset);
		break;
	 case _AIO_WRITE:
		flag = aio_write(req->fd,req->data,req->count,offset);
		break;
	 case _AIO_CANCEL:
		flag = 0;
		break;
	default:break;
	}
	if(flag<0) 
	{
	 req->status = _AIO_STATUS_FAIL;
	 req->ret->aio_return = -1;
	 req->ret->aio_errno = errno;
	}
	else
	{
	 req->status = _AIO_STATUS_OK;
	 req->ret->aio_return = flag;
	}
	 req->ret->tid = pthread_self();
}
void* Thread::Execute(void* _thread)
{
   int result;
   Thread *thread = (Thread*)_thread;
   result = thread->Execute();
   return (void*)result;
}

