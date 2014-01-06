/*
 * =====================================================================================
 *
 *       Filename:  RequestMap.h
 *
 *    Description:  from request to map to agent
 *
 *        Version:  1.0
 *        Created:  2011年04月12日 00时35分22秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (), 
 *        Company:  NDSL UESTC
 *
 * =====================================================================================
 */
#ifndef _REQUEST_MAP_H_
#define _REQUEST_MAP_H_
#include "Agent.h"
#include <map>
using namespace std;


class RequestMap{
    public:
       static RequestMap* getInstance();
        bool request(unsigned long long,unsigned int);
        bool getMemAgent(unsigned long long,unsigned int&);
        void clear(const unsigned int);
        ~RequestMap();

    private:
        RequestMap(){}
        RequestMap(const RequestMap&);
        map<unsigned long long,unsigned int> m_mAgent;


};
#endif
