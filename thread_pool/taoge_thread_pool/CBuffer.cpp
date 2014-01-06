#include "CBuffer.h"

CBuffer::CBuffer(int fd)
	:m_sFd(fd),m_wOut(0),m_wLength(0),m_rLength(0),m_rIn(0),m_rOffset(0)
{
	
	//数据包数据缓存信息
	m_pRData = new char[BUFFERSIZE];
	memset(m_pRData,'\0',BUFFERSIZE);
	m_pWData = new char[BUFFERSIZE];
	memset(m_pWData,'\0',BUFFERSIZE);
	m_pHead = new char[sizeof(int)+1];
	memset(m_pHead,'\0',sizeof(int)+1);
}
CBuffer::~CBuffer()
{
	struct tagHead *head;
	while(!m_pqRead.empty())
	{
	  head = m_pqRead.front();
	  m_pqRead.pop();
	  delete[] head->msg;
	  delete head;
	}
	while(!m_pqWrite.empty())
	{
	  head = m_pqWrite.front();
	  m_pqWrite.pop();
	  delete[] head->msg;
	  delete head;
	}
	delete[] m_pRData;
	delete[] m_pWData;
	delete[] m_pHead;
	
}
//主要工作是 缓存数据包，区分一个数据包是否形成
int CBuffer::readSocket(struct tagHead *&head)
{
	struct tagHead *_head;
	int len = readData();
//	getchar();
	while(len>0)//读到没有数据可读为止
	{
	  if(m_rIn==m_rLength&&m_rIn!=0) //一个数据包已经完成了,放入缓存队列
	  {
		_head = new struct tagHead;
		_head->length = m_rLength;
		_head->msg = new char[m_rLength+1];
		memset(_head->msg,'\0',m_rLength+1);
		memcpy(_head->msg,m_pRData,m_rLength);
		//数据包形成了，进入缓冲队列
		m_pqRead.push(_head);
//		cout<<"get new packet:"<<_head->msg<<endl;//invalid read of size
		m_rIn = 0;
		m_rLength = 0;
	  }
	   len = readData();//继续读取数据
//	   cout<<"len(while):"<<len<<endl;
	}
	//从缓存队列中取出一个数据
	if(!m_pqRead.empty())  {
		head=m_pqRead.front();
		m_pqRead.pop();
        //invalid read of size 8
//		cout<<"length:"<<head->length<<" msg:"<<head->msg<<endl;
		return 1;
	}
	//读取数据错误
	if(len==-1&&(errno==EINTR||errno==EAGAIN||errno==EWOULDBLOCK))	
		return 0;
	//客户端关闭
	if(0==len) return -1;
    return 0;
}

//主要的工作是区分长度域，数据域
int CBuffer::readData()
{
  int len=0;
  if(0==m_rLength) //数据包本来的长度头部域
  {	
//	cout<<"read header:"<<m_rOffset<<"len"<<len<<endl;
	len = read(m_sFd,m_pHead+m_rOffset,4); //4个字节的数据头部长度
	if(len<0) goto out;
	m_rOffset += len;
//	cout<<"read len:"<<len<<" head offset:"<<m_rOffset<<endl;
	if(len==sizeof(int)||m_rOffset==sizeof(int)){ //数据包的长度满足了
	m_rLength = *((int*)m_pHead);
//	cout<<"get packet length:"<<m_rLength<<endl;
	m_rIn = 0;
	//初始化头部数据包,接受下一个
	memset(m_pHead,'\0',sizeof(int)+1);
	m_rOffset = 0;
	}
//	getchar();
	return len;
  }
  else
  {
	len = read(m_sFd,m_pRData+m_rIn,m_rLength-m_rIn);
		//直接读取数据包指定长度
	if(len>0) m_rIn += len;
//	cout<<"read data:"<<m_rIn<<" this:"<<len<<endl;
	goto out;
  }
out:
{
  if(len>0) return len;
  else 
	if(-1==len&&errno==EINTR) return 1;//让调用者去再调用
  else //没有数据可读了
	if(-1==len&&(errno==EWOULDBLOCK||errno==EAGAIN)) return 0;
  else  {
	cerr<<"len:"<<len<<"read msg error:"<<strerror(errno)<<endl;
	return -1;//真的错误了
	}
}
}

int CBuffer::writeSocket(struct tagHead* head)
{	
	int length;
	m_pqWrite.push(head);
	length = writeData();
	while(length>0) //发送数据直到不能发送为止
	{
		length = writeData();
//	    cout<<"length:"<<length<<endl;
        if(-1==length||errno==EINTR) length=1;
    } 
	if(-1==length)
    {
        if((errno==EAGAIN||errno==EWOULDBLOCK))
            return 0;
        else return -1;
    }
        return 0;
}
//发送信息，每个以数据包为准
int CBuffer::writeData()
{
	int len;
	struct tagHead *head;
	if(m_wOut == m_wLength) 
	//已经发送的等于本来发送的长度,数据包发送完:-)
	{
	  if(!m_pqWrite.empty()) //继续下一次的发送
	  {
		head = m_pqWrite.front();
		m_wOut = 0;
//		cout<<"writting data:"<<head->msg<<"("<<head->length<<")"<<endl;
		m_wLength = head->length+sizeof(int);
		memset(m_pWData,'\0',BUFFERSIZE);
        memcpy(m_pWData,&(head->length),sizeof(int));//复制信息长度
		//复制数据内容
		memcpy(m_pWData+sizeof(int),head->msg,m_wLength-sizeof(int));
		//发送完成，清除信息，释放空间
		m_pqWrite.pop();
		delete []head->msg;
		delete head;	
		return 1;
	  }
		return 0;
	}
	else
	{
	//发送数据
	//返回0代表没有写入数据
//	cout<<"msg length:"<<m_wLength<<" already:"<<m_wOut<<endl;
	len = write(m_sFd,m_pWData+m_wOut,m_wLength-m_wOut);
	if(len<0){
	if(errno==EINTR) return 1;
	else if(errno==EWOULDBLOCK||errno==EAGAIN) return 0;
	else 
	{
		cerr<<"len:"<<len<<"send msg error:"<<strerror(errno)<<endl;
		return -1;
	}
	}
	else m_wOut += len;
//	cout<<"发送数据长度:"<<len<<" length:"
//		<<m_wLength<<" out:"<<m_wOut<<endl;
	return len;
	}
}
