#ifndef _AGENT_H_
#define _AGENT_H_
struct req_t;

class Agent{
public:
	Agent(){}
	virtual int readAgent()=0;
	virtual int writeAgent()=0;
	virtual int getFd()=0;
    virtual void do_req(struct req_t*&){}
	virtual ~Agent(){}

};


#endif
