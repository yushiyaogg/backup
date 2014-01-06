#include "header.h"

void doRequest(int);
void *enQueue(void*);

int main()
{
  int pipefd[2];
  struct req_t *req;
 pthread_t tid;
 if(pipe(pipefd)!=0)
 {
	cerr<<"create pipe error!"<<endl;
	exit;
 }
 if(pthread_create(&tid,NULL,enQueue,(void*)&(pipefd[1]))!=0)
 {
	cerr<<"create the producer thread error!"<<endl;
	return -1;
 } 
 doRequest(pipefd[0]);
 if(pthread_join(tid,NULL)!=0)
 {
	cerr<<"wait the thread:"<<tid<<" error!"<<endl;
 }
 cout<<"main is exiting!"<<endl;
 return 0;
}

//从管道中读取处理结果
void doRequest(int rfd)
{
	int n;
	struct req_t *req;
//	req=(struct req_t*)malloc(sizeof(struct req_t*));
	req = new struct req_t;
	while(1)
	{
	n=read(rfd,&req,sizeof(struct req_t*));
	if(n==-1&&errno!=EINTR)
	{
	 cerr<<"read from pipe error!"<<endl;
	}
	else cout<<"read number:"<<n<<endl;
	if(req->rid!=0)
	cout <<"get result :"<<req->rid<<endl;
	delete req;
	}
	delete req;
	
}
void* enQueue(void* fd)
{
	int wfd = *((int*)fd);
	int i=1;
	int length;
	struct req_t *req ;
	while(i<1000)
	{
//	  req=(struct req_t*)malloc(sizeof(struct req_t));
	  req = new struct req_t;
	  req->rid = i;
	  req->_req = i;
	  cout<<"write into the pipe:"<<" sizeof:"<<sizeof(req)
	  <<" "<<req->rid<<endl;
	  length=write(wfd,&req,sizeof(struct req_t*));
		if(length<0&&errno!=EINTR) {
		delete req;
		cerr<<"write into the pipe error:"<<strerror(errno)<<endl;	
	  }
		else cout<<"length:"<<length<<endl;
	  	i++;
	}
}
