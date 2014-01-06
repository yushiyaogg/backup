/*
 * =============================================================================
 * 
 *       Filename:  BaseHeader.h
 * 
 *    Description:  
 * 
 *        Version:  1.0
 *        Created:  2011-05-10 14:30:28
 *  Last Modified:  2011-05-10 14:30:28
 *       Revision:  none
 *       Compiler:  gcc
 * 
 *         Author:  Shi Wei (sw), shiwei2012@gmail.com
 *        Company:  NDSL UESTC
 * 
 * =============================================================================
 */

#ifndef _BASE_HEADER_H_
#define _BASE_HEADER_H_

#include <sys/types.h>
#include <stdint.h>

const int CONNECTING = 0;
const int CONNECTED = 1;
const int CONNECTFAILED = -1;
const int MAXRECONNECTTIMES = 3;
#define IPV4 4
#define IPV6 6
#define IPV4ANYADDR "0.0.0"
#define IPV6ANYADDR "::1"

const unsigned int HEADER_SIZE = sizeof(uint32_t) * 5;

struct MsgHeader
{
    uint32_t cmd;	// ��Ϣ����
    uint32_t length; //������Ϣ����
    uint32_t error;
    uint32_t para1;
    uint32_t para2;

    MsgHeader() :
        cmd(0),
        length(0),
        error(0),
        para1(0),
        para2(0)
    {

    }

    ~MsgHeader() {

    }
};

#endif

