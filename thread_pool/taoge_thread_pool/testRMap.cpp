/*
 * =====================================================================================
 *
 *       Filename:  testRMap.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011��04��12�� 01ʱ07��48��
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (), 
 *        Company:  NDSL UESTC
 *
 * =====================================================================================
 */
#include "RequestMap.h"
#include "MemAgent.h"


int main()
{
    unsigned int address;
    RequestMap *p=RequestMap::getInstance();
    MemAgent *agent;
for(int i=0;i<10;i++)
{
    agent=new MemAgent(i);
    p->request(i,(unsigned int)agent);
}
for(int i=0;i<10;i++)
{
   if(p->getMemAgent(i,address))
   {
    agent=(MemAgent*)address;   
    cout<<"id:"<<agent->getFd()<<endl;
   }
   else cout<<"get fd error:"<<endl;
}
return 0;
}
