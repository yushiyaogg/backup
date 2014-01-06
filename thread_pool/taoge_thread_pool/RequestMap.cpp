/*
 * =====================================================================================
 *
 *       Filename:  RequestMap.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011年04月12日 00时47分11秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (), 
 *        Company:  NDSL UESTC
 *
 * =====================================================================================
 */
#include "RequestMap.h"
#include "header.h"

RequestMap* RequestMap::getInstance()
{
    static RequestMap request;
    return &request;
}
void RequestMap::clear(const unsigned int agent)
{
     for(map<unsigned long long,unsigned int>::iterator it=m_mAgent.begin();
		it!=m_mAgent.end();)
     {
         map<unsigned long long,unsigned int>::iterator erase_element = it++;
//         cout<<"add:"<<it->second<<endl;
         if(it->second == agent) 
         {   
         m_mAgent.erase(erase_element);
//         cout<<"address:"<<it->second<<endl;
         }
     }
}
bool RequestMap::request(unsigned long long rid,unsigned int agent)
{

  bool flag = m_mAgent.insert(pair<unsigned long long,unsigned int>(rid,agent)).second;
  return flag;
}
bool RequestMap::getMemAgent(unsigned long long rid,unsigned int&agent)
{
    map<unsigned long long,unsigned int>::iterator it;
    

    it = m_mAgent.find(rid);
    if(it==m_mAgent.end()) return false;
    agent =(*it).second;
    m_mAgent.erase(it);
//    cout<<"getMemAgent:"<<rid<<endl;
    return true;
}

RequestMap::~RequestMap()
{
    for(map<unsigned long long,unsigned int>::iterator it=m_mAgent.begin();it!=m_mAgent.end();)
            m_mAgent.erase(it++);
}
