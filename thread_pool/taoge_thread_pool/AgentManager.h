/*
 * =====================================================================================
 *
 *       Filename:  AgentManager.h
 *
 *    Description:  Agent Manager
 *
 *        Version:  1.0
 *        Created:  2011年04月12日 00时12分55秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (), 
 *        Company:  NDSL UESTC
 *
 * =====================================================================================
 */
#ifndef _AGENT_MANAGER_H_
#define _AGETN_MANAGER_H_

#include "Agent.h"

class AgentManager
{
    public:

AgentManager* getInstance();
MemAgent* getAgent();
int closeAgent(MemAgent*);

    private:
AgentManager();
AgentManger(const AgentManager&);

struct linklist
{
struct linklist *next;
MemAgent* agent;
};

struct linklist *active,*expire;

void initList(struct linklist*);

};
#endif
