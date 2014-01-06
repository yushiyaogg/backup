/*
 * =====================================================================================
 *
 *       Filename:  server.h
 *
 *    Description:  the file is the head file of the client.c
 *
 *        Version:  1.0
 *        Created:  2011年08月29日 08时53分54秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (), 
 *        Company:  NDSL UESTC
 *
 * =====================================================================================
 */
#include <sys/socket.h>
#include <unistd.h>
#include <strings.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>

#define LISTENQ 2000
#define SA struct sockaddr
#define MAXLINE 102400
#define MAXFD  10000
