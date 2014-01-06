#ifndef _CBUFFER_H_
#define _CBUFFER_H_
#include <unistd.h>
#include "header.h"
/**
**非阻塞缓冲区读写问题*
*数据包的组成:长度(4字节) 信息
*假设数据包的读取长度不一定一次性成功
*/
class CBuffer
{
public:
	CBuffer(int);
	int readSocket(struct tagHead*&head);
	int writeSocket(struct tagHead*head);
	~CBuffer();
private:
	int readData();
	int writeData();
	int m_sFd;
	//读取数据包
	int   m_rLength;//数据包本来的长度
	int   m_rIn;//已经读取数据包的长度
	unsigned int m_rOffset;//包头部读取长度
	char *m_pRData;//数据包数据
	char *m_pHead;//数据包的头部
	//发送数据包
	char *m_pWData;
	int   m_wOut;//已经发送的长度
	int   m_wLength;//数据包本来的长度
	//非阻塞读写队列，缓存每一个数据包
	queue <struct tagHead* > m_pqRead;
	queue <struct tagHead* > m_pqWrite;
};
#endif
