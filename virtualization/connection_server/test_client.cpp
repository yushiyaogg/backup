/*
 * =====================================================================================
 *
 *       Filename:  test_client.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/20/12 19:28:25
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
#define PORTNUM 11223
using namespace std;
struct message_head
{
    unsigned int cmd;
    unsigned int len;
    unsigned int para1;
    unsigned int para2;
    unsigned int para3;
};
int main(int argc,char **argv)
{
    int sockfd;
    struct message_head head;
    struct sockaddr_in servaddr;
    char tmp[]="yushiyao yushiyao";
    char *ptr;

    if(argc!=2)
        cout <<"input the ip address"<<endl;
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORTNUM);
    inet_pton(AF_INET,argv[1],&servaddr.sin_addr);
    connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    head.len = sizeof(tmp)-1;
    write(sockfd,&head,sizeof(head));
    write(sockfd,tmp,head.len);
    read(sockfd,&head,sizeof(head));
    ptr = new(char[head.len]);
    read(sockfd,ptr,head.len);
    ptr[head.len+1] ='0';
    cout <<ptr<<endl;
}
