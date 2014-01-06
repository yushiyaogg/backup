#include "MidServer.h"
#include "MemAgent.h"
#include "RequestMap.h"
#include <fstream>

const int MidServer::len = sizeof(struct req_t*)+1;
int MidServer::count = 0;
ofstream mout("midserver");

MidServer::MidServer():m_rIn(0){
	
	if(pipe(pipefd)!=0)
	{
	  cerr<<"create pipe error!"<<endl;
	}
	m_pRm = RequestMap::getInstance();
	m_pAddress = new char[len];
	memset(m_pAddress,'\0',len);
//	cout<<"read fd:"<<this->getFd()<<endl;
//	cout<<"MidServer read fd"<<pipefd[0]<<" write fd:"<<pipefd[1]<<endl;	
	if(this->setNonBlock(pipefd[0])<0)
  	{
		cerr<<"set Mid server read fd error!"<<endl;
	}
    if(setNonBlock(pipefd[1])<0)
        cerr<<"set Mid server writting fd error:"<<strerror(errno)<<endl;

}

MidServer* MidServer::getInstance()
{
	static MidServer pMidServer;
	return &pMidServer;
}

int MidServer::setNonBlock(int fd)
{
	int flag;
	if((flag=fcntl(fd,F_GETFL,0))<0)
	{
	cerr<<"set nonblock error:"<<strerror(errno)<<endl;
	return -1;
	}
	flag |= O_NONBLOCK;
	if(fcntl(fd,F_SETFL,flag)<0)
	{
	  cerr<<"set nonblock error:"<<strerror(errno)<<endl;
	 return -1;
	}
	return 0;
}
int MidServer::readAgent()
{
	MemAgent *agent;
	unsigned int address;
	struct req_t* req;
	int length=0;
	assert(sizeof(unsigned int)==sizeof(struct req_t*));
	length = readSocket();   
    while(length>0)
      {
       if(m_rIn==sizeof(struct req_t*)) 
		//一个地址已经形成了,保存起来，并清除原来的缓冲区内容
	  {
		address = *((unsigned int*)m_pAddress);
		m_pqHead.push(address);
		memset(m_pAddress,'\0',len);
		m_rIn =0;
       }
       length = readSocket();
       if(-1==length&&errno==EINTR) continue;
//       cout<<"length:"<<length<<endl;
      }
      while(!m_pqHead.empty())
      {
        address = m_pqHead.front();
        req = (struct req_t*)address;
//		cout<<"head empty"<<endl;
        if(m_pRm->getMemAgent(req->rid,address))
        {
		agent = (MemAgent*)address;
         agent->do_req(req);		
        }
        else 
        {
//        cout<<"error cann't get the agent!"<<endl;
 //       dealWith(req); 
	 ;
        }
//        mout<<"rid:"<<req->rid<<endl;
        delete req->ret;
		delete[] req->data;
        delete req;
        m_pqHead.pop();
      }
    /*  
    if(m_rIn==sizeof(struct req_t*))
    {
      address = *((unsigned int*)m_pAddress);
      memset(m_pAddress,'\0',len);
      m_rIn = 0;
      req = (struct req_t*)address;
      count++;
      req = (struct req_t*)address;
      if(m_pRm->getMemAgent(req->rid,address))
      {
        agent = (MemAgent*)address;
        agent->do_req(req);
        mout<<"rid:"<<req->rid<<endl;
      }
      else cout<<"error cann't get the agent!"<<endl;
      dealWith(req);
      delete req->ret;
      delete[] req->data;
      delete req;
    }*/
    if(length==-1) 
    {
	if(errno==EAGAIN||errno==EWOULDBLOCK) return 0;
	return -1;
    }
	return 0;	
}
//处理具体的命令后的回调
void MidServer::dealWith(struct req_t* req)
{
	count++;
	if(req->ret->aio_return >0&&req->status==_AIO_STATUS_OK)
	{
	  cout<<"req_id"<<req->rid
		<<" Thread("<<count<<") "<<req->ret->tid<<" data:"
        <<(char*)req->data<<endl;
	}
	else
	{
	  cout<<"req_id"<<req->rid<<" Thread("<<count<<")"<<req->ret->tid
		<<"error :"<<strerror(req->ret->aio_errno)<<endl;
	}
//	delete p->data;
}
int MidServer::writeAgent()
{
	return 0;
}
//只负责读，不负责具体的处理事务
size_t MidServer::readSocket()
{
   int length,rfd,offset;
   rfd = pipefd[0];
   offset = m_rIn;
//   cout<<"befor readSocket:"<<offset<<endl;
   length = read(rfd,m_pAddress+offset,sizeof(struct req_t*)-offset);
   if(length<0)
   {
    if(errno==EINTR) return 1;//继续可以读
    else if(errno==EAGAIN||errno==EWOULDBLOCK) return -1;//不能继续读了
   }
  // cout<<"readSocket:"<<m_pAddress<<" "<<m_rIn
//	<<" length:"<<length<<endl;
   m_rIn +=length;
   return length;
}

MidServer::~MidServer(){

	close(pipefd[0]);
	close(pipefd[1]);
	delete[]  m_pAddress;
	while(!m_pqHead.empty()) {
//	 cout<<"MidServer get result:"<<m_pqHead.front()<<endl;
	 m_pqHead.pop();
	}
//	cout<<"destruct function of MidServer"<<endl;
}
