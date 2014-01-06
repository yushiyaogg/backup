/*
 * =====================================================================================
 *
 *       Filename:  ClientAgent.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/14/2013 02:16:59 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (), 
 *        Company:  NDSL UESTC
 *
 * =====================================================================================
 */
#ifndef _CLIENTAGENT_H
#define _CLIENTAGENT_H

#include <comm/TCPAgent.h>
#include <string>
class ClientAgent:TCPAgent
{
pubulic:
    ClientAgent(Epoll *epl):TCPAgent(epl)
    {
    
    }
    void readBack(InReq &req);
    void writeBack(bool result);

//    MsgHeader msgheader;
//    string msg;
    class  Worker* worker;
    ThreadPool* pool;
}

#endif
