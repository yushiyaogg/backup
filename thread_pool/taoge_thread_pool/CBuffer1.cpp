#include "CBuffer.h"
#include "header.h"

CBuffer::CBuffer(int fd)
	:m_sFd(fd),m_wOut(0),m_wLength(0),m_rLength(0),mrIn(0)
{
	
	//数据包数据缓存信息
	m_pRData = new char[BUFFERSIZE];
	memset(m_pRData,'\0',BUFFERSIZE);
	m_pWData = new char[BUFFERSIZE];
	memset(m_pWData,'\0',BUFFSIZE);
	
}

bool CBuffer::isLastFinish()
{
	return m_wOut==m_wLength;
}

int CBuffer::readSocket(struct tagHead *head)
{
    int flag;
    if(m_rIn==m_rLength) //一次读取已经完成,将数据发送给调用者
    {
	if((m_rLength!=0)&&(m_rLength==strlen(m_pRData)))
		//长度相等,代表读取已经完成,进入读取队列
	{
	    struct tagHead _head;
	    _head.length = m_rLength;
	    _head.msg = new char[m_rLength];
	    memcpy(m_pRData,_head.msg,m_rLength);
	    m_pqRead.push(&_head);
	    //清空已经读取的内容
	    m_rLength = 0;
	    m_rIn = 0;
	    flag = 1;
	}
	//初始化下一次的读取
	memset(m_pRData,'\0',BUFFERSIZE);
	if(readData()<0)
	{
		cerr<<"read from fd "<<fd<<" error"<<endl;
		return -1;
	}
	//读一次，判断数据是否读取完成
	else
	{
	     //数据真的读完了
	     if((m_rLength!=0)&&(m_rLength ==strlen(m_pData)))
	     {
		
	     }
	}
    } 
    else  //上次的数据没有读取完成，从上次继续读取
    {
	if(readData()<0)
	{
	  return -1;
	}	
    }
	return flag;
}


