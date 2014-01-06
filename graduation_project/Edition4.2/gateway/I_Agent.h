/*
 * =====================================================================================
 *
 *       Filename:  I_Agent.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/12/12 14:55:48
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  yushiyao (), yushiyaogg@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#ifndef _I_AGENT_H_
#define _I_AGENT_H_

#include "head.h"
#include "Epoll.h"
#include "I_Manager_Agent.h"
#include "Buffermanager.h"
#include "ReadAgent.h"
#include "WriteAgent.h"
class I_Agent:public Agent
{
    public:
        class ReadAgent I_read;
        class WriteAgent I_write;
        class Socket_I_O_Buff Writebuff;
        class Buffermanager* Readbuff;
        class Buffermanager Readbuff_head;
        class Buffermanager Readbuff_data;
        struct PDU pdu;

        int read_len;
        int read_stat;


        int readagent();
        int writeagent();
        int getfd();
        int package_head_data();
        I_Agent(int);
        ~I_Agent();
};

#endif
