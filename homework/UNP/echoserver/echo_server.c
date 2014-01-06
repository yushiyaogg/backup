/*
 * =====================================================================================
 *
 *       Filename:  server.c
 *
 *    Description:  the echo-server using the epoll
 *
 *        Version:  1.0
 *        Created:  2011年08月26日 16时00分22秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (), 
 *        Company:  NDSL UESTC
 *
 * =====================================================================================
 */
#include "server.h"
int nonblocksetting(int fd)
{
    int val;
    if((val = fcntl(fd, F_GETFL, 0)) == -1)
    {
        printf("fcntl error\n");
        return -1;
    }
    if(fcntl(fd, F_SETFL, val|O_NONBLOCK) == -1)
    {
        printf("fcntl error\n");
        return -1;
    }
    return 0;
}
int serv_echo(int fd)
{
    char buf[MAXLINE];
    char *bufi, *bufo;
    int  nread, nwrite;
    int  endmark;
    endmark = 0;
    bufi = bufo = buf;
    if((nread = read(fd, bufi, &buf[MAXLINE] - bufi)) < 0)
    {
        if(errno != EWOULDBLOCK)
        {
            printf("read error\n");
            close(fd);
            return -1;
        }
    }
    else if(nread == 0)
    {
        endmark = 1;
        goto writesock;
    }
    else
    {
        bufi = bufi + nread;
writesock:
        if((nwrite = write(fd , bufo, bufi - bufo)) < 0)
        {
            if(errno != EWOULDBLOCK)
            {
                printf("write error\n");
                close(fd);
                return -1;
            }
        }
        else
        {
            bufo = bufo + nwrite;
            if(bufo == bufi)
            {
                if(endmark == 1)
                {
                    close(fd);
                    return 0;
                }
                else
                {
                    bufi = bufo = buf;
                }
            }
        }
    }
}
int main(int argc, char *argv[])
{

    if(argc != 3)
    {
        printf("please input the socketnum and the max fd can be connect\n");
        return -1;
    }
    int                     listenfd, epollfd,connfd;
    int                     nfd;
    int                     i;//used for the loop to check the nfd
    struct sockaddr_in      cliaddr, servaddr;
    socklen_t               clilen;
    struct epoll_event      tempev, sockev[MAXFD];
    int                     port = atoi(argv[1]);
    int                     epollmax = atoi(argv[2]);
    signal(SIGPIPE,SIG_IGN);
    if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("socket error\n");
        return -1;
    }
    if(nonblocksetting(listenfd) == -1)
    {
        printf("nonblocksetting error\n");
        return -1;
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
    if(bind(listenfd, (SA *)&servaddr, sizeof(servaddr)) == -1)
    {
        printf("bind error: %s\n", strerror(errno));
        return -1;
    }
    if(listen(listenfd, LISTENQ) == -1)
    {
        printf("listen error\n");
        return -1;
    }
    if((epollfd = epoll_create( epollmax )) < 0)
    {
        printf("epoll_creat error\n");
        return -1;
    }
    tempev.data.fd = listenfd;
    tempev.events = EPOLLIN ;
    if(epoll_ctl(epollfd, EPOLL_CTL_ADD, listenfd, &tempev) < 0)
    {
        printf("epoll_ctl error\n");
        return -1;
    }
    for(  ;;)
    {
        nfd = epoll_wait(epollfd, sockev, epollmax, -1);
        for(i = 0; i < nfd; i++)
        {
            if(sockev[i].data.fd == listenfd)
            {
                clilen = sizeof(cliaddr);
                if((connfd = accept(listenfd, (SA *)&cliaddr, &clilen)) < 0)
                {
                    printf("accept error\n");
                    continue;
                }
                if(nonblocksetting(connfd) == -1)
                {
                    printf("nonblocksetting error\n");
                    continue;//return?
                }
                tempev.data.fd = connfd;
                tempev.events = EPOLLIN | EPOLLERR;
                if(epoll_ctl(epollfd, EPOLL_CTL_ADD, connfd, &tempev) < 0)
                {
                    printf("epoll_ctl error\n");
                    continue;//return?
                }
            }
            else if(sockev[i].events & EPOLLIN)
            {
                serv_echo(sockev[i].data.fd);
            }
            else
            {
                printf("the error fd is %d and the events is %d\n",sockev[i].data.fd,sockev[i].events);
            }
        }
    }
    return 0;
}
