/*
 * =====================================================================================
 *
 *       Filename:  head.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/15/12 09:45:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  yushiyao (), yushiyaogg@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#ifndef _HEADER_H
#define _HEADER_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <utility>

#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <byteswap.h>

using namespace std;

#define MAXEPOLL 100
#define SA struct sockaddr
#define TCP_SOCKET_SIZE 64*1024
#define DISK_BLOCK_NUMBER 128*1024
#define MESG_HEAD_LEN 12
#define BLOCK_SIZE 512
#define SERV_PORT 32600

//read return value
#define READ_ERROR -1
#define READ_END    0
#define READ_BLOCK  1
#define READ_SUCCESS 2

//write return value
#define WRITE_ERROR -1
#define WRITE_BLOCK  1
#define WRITE_SUCCESS 2

//mesg_head:opcode
#define READ_DISK 0x00
#define WRITE_DISK 0x01
#define RESPONSE_READ 0x10
#define RESPONSE_WRITE 0x11

//mesg_head:status
#define WRITE_CMND 0x00
#define DATA_OUT_CMND 0x10

#define WRITE_RESPONSE_FAILD 0x00
#define WRITE_RESPONSE_SUCCESS 0x01
#define DATA_OUT_RESPONSE_FAILD 0x10
#define DATA_OUT_RESPONSE_SUCCESS 0x11
struct mesg_head{
    unsigned char opcode;
    unsigned char write_status;
    unsigned short len;
    unsigned int addr;
    unsigned int itt;
};

#endif
