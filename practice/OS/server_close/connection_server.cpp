/*
 * =====================================================================================
 *
 *       Filename:  connection_server.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/23/12 17:54:45
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#define  PORTNUM 50001
using namespace std;
struct message_head
{
    unsigned int cmd;
    unsigned int len;
    unsigned int para1;
    unsigned int para2;
    unsigned int para3;
};
int main(int argc,char ** argv)
{

    int listenfd,connfd;
    socklen_t clilen;
    struct sockaddr_in servaddr,cliaddr;
    struct message_head head;
    char *ptr;
    int ret;

    listenfd = socket(AF_INET, SOCK_STREAM,0);
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port =htons(PORTNUM);
    if(bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
    {
        cout<<"bind error"<<endl;
        return -1;
    }
    listen(listenfd,50);
    while(1)
    {
        clilen = sizeof(cliaddr);
        if((connfd = accept(listenfd,(struct sockaddr*)&cliaddr,&clilen))< 0)
        {
            cout<<"accept error"<<endl;
            continue;
        }
        cout << "before close"<<endl;
//	int ret = write(connfd,"abcde",3);
 //       close(connfd);
	shutdown(connfd,2);
        continue;
        /*
        if((ret = read(connfd,&head,sizeof(head))) < 0)
        {
            cout <<"read head error"<<endl;
            continue;
        }
        ptr = new(char[head.len]);
        if((ret = read(connfd,ptr,head.len)) < 0)
        {
            cout<<"read body error"<<endl;
            delete []ptr;
            continue;
        }
        if(strcmp(ptr,"xiepeng xiepeng") == 0)
        {
            char tmp1[] = "192.168.12.2 3389 administrator uestc8020_\n";
            delete []ptr;
            ptr = new(char[sizeof(tmp1)-1]);
            memcpy(ptr,tmp1,sizeof(tmp1) -1);
            head.len = sizeof(tmp1)-1;
            write(connfd,&head,sizeof(head));
            write(connfd,ptr,sizeof(tmp1)-1);
            delete ptr;
            close(connfd);
            continue;
        }
        else if(strcmp(ptr,"yushiyao yushiyao") == 0)
        {
            char tmp2[] = "192.168.12.5 3389 administrator uestc8020_\n";
            delete []ptr;
            ptr = new(char[sizeof(tmp2)-1]);
            memcpy(ptr,tmp2,sizeof(tmp2) -1);
            head.len = sizeof(tmp2)-1;
            write(connfd,&head,sizeof(head));
            write(connfd,ptr,sizeof(tmp2)-1);
            delete ptr;
            continue;
        }
        else
        {
            delete ptr;
            close(connfd);
            continue;
        }*/

    }
}
