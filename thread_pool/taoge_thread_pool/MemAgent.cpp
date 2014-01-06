#include "MemAgent.h"
#include "CBuffer.h"
#include "FileMap.h"
#include "Scheduler.h"
#include "RequestMap.h"

unsigned long long MemAgent::num = 1;

MemAgent::MemAgent(int cFd):m_cFd(cFd){
	
	m_pqueue =Scheduler::getInstance();
    m_pRm = RequestMap::getInstance();
	m_pBuffer = new CBuffer(m_cFd);
//    cout<<"memAgent:"<<m_cFd<<endl;
}

int MemAgent::readAgent()
{
	struct tagHead *head;
	int length;
//	cout<<"ready for reading!"<<endl;
	length = m_pBuffer->readSocket(head);
//	cout<<"readAgent:"<<length<<endl;
	if(length<0) return -1;
	if(1==length)
	{
//	cout<<"read from the client:"<<head->msg<<endl;
	dealWith(head);
	delete[] head->msg;
    delete head;
	}
	return 0;
}
//
int MemAgent::send(struct tagHead*_head)
{
	assert(_head->length==strlen(_head->msg));
//	cout<<"send to "<<endl;
	m_pqHead.push(_head);
//	cout<<"size:"<<m_pqHead.size()<<endl;
	return 0;
}
void MemAgent::dealWith(struct tagHead*head)
{
  struct stat buf;
  struct req_t *req;
  FileMap *fileMap = FileMap::getInstance();
  int fd = fileMap->getFileFd(head->msg); 
  if(fstat(fd,&buf)<0)
  {
	cerr<<"get file "<<fd<<" size error:"<<strerror(errno)<<endl;
	return;
  }
  int size = buf.st_size;
  int offset;
  offset = 0;
//  cout<<"file size:"<<size<<endl;
  while(size>0)
  {
	req = new struct req_t;
	req->fd = fd;
	req->rid = num;
	req->req_op = _AIO_READ;
	req->data = new char[MAXLINE+1];
	memset(req->data,'\0',MAXLINE);
	req->count = MAXLINE;
	req->status = _AIO_STATUS_SUBMIT;
	req->offset = offset;
	req->ret = new aio_ret_t;
	req->ret->data = 0;
	req->ret->data = (unsigned int)this;
	m_pRm->request(num,(unsigned int)this);
    if(m_pqueue->request(req)<0)
	{
	 cerr<<"send the request into the queue error!"<<endl;
	 delete [](char*)req->data;
     delete req->ret;
     delete req;
	}
	else 
	{
	;
//	cout<<" req id:"<<req->rid<<" size:"<<size<<endl;
	}
	num++;
	size -= MAXLINE;
	offset += MAXLINE;
  }
}

void MemAgent::do_req(struct req_t* req)
{

   struct tagHead *head;

   assert(strlen(req->data)==(req->ret->aio_return));
   if(req->ret->aio_return>0&&req->status==_AIO_STATUS_OK)
   {
    head = new struct tagHead;
	head->length =req->ret->aio_return;	
	head->msg = new char[head->length+1];
	memset(head->msg,'\0',head->length+1);
    memcpy(head->msg,req->data,head->length);
//	cout<<"msg:"<<head->msg<<endl;
	send(head);
   }
   else 
	{
	cerr<<"read fail!"<<endl;
	}
}	

int MemAgent::writeAgent()
{
	struct tagHead *head;
	int length=0;
	while(!m_pqHead.empty()&&-1!=length)
	{
	  head = m_pqHead.front();
	  length = m_pBuffer->writeSocket(head);
//	  cout<<"write length:"<<length<<endl;
	  m_pqHead.pop();
	}
 //   else
//	{
//        cout<<"no data to send!"<<endl;
//	}
	return length;
}

MemAgent::~MemAgent()
{
	struct tagHead *head;
	while(!m_pqHead.empty())
	{
	  head = m_pqHead.front();
      m_pqHead.pop();
      delete []head->msg;
	  delete head;
	}
	delete m_pBuffer;
}
