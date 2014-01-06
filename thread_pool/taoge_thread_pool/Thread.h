#ifndef _THREAD_H_
#define _THREAD_H_
#include "header.h"

//struct pipeset;

class Thread
{
public:
  Thread(struct pipeset);
  static  void* Execute(void*);
  int Execute();
  pthread_t getTid(){return tid;}
  ~Thread();
private:
    static unsigned long num;
	void dealWith(struct req_t*);
	pthread_t tid;
	struct pipeset set;
    vector<unsigned int> m_vAddr;	
    void setNonBlock(int);

};

#endif
