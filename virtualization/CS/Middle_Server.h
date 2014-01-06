/*
 * =====================================================================================
 *
 *       Filename:  Middle_Server.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/14/2013 03:17:37 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (), 
 *        Company:  NDSL UESTC
 *
 * ====================================================================================
 */ 
#ifndef _MIDDLE_SERVER_H
#define _MIDDLE_SERVER_H
include ""
class Middle_server
{
    public:
        Middle_server();


        int fd[2];
        Epoll* epl;
}
