#ifndef _MID_SERVER_H_
#define _MID_SERVER_H_
//处理线程的结果反馈，通知上面的Agent
//单件模式
#include "Agent.h"
#include "header.h"

class RequestMap;
struct req_t;
//struct pipeset;

class MidServer:public Agent{
public:
      static MidServer* getInstance();
      int getWriteFd(){return pipefd[1];}
      inline int getFd(){return pipefd[0];}	
      int readAgent();
      int writeAgent();
      ~MidServer();
private:
	MidServer();
	MidServer(const MidServer&);
	MidServer& operator=(MidServer&);
	int setNonBlock(int);
	void dealWith(struct req_t*);
	size_t readSocket();	
	queue <unsigned int> m_pqHead;
	int pipefd[2];
	char *m_pAddress;
    RequestMap *m_pRm;
	unsigned int m_rIn; //读取的长度
	static const int len;
	static int count;
};

#endif
