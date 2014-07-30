#include<sys/socket.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include <strings.h>
#include <stdlib.h>
#include<errno.h>
#define SERV_PORT 50001

#define  num  2000

#define  SA struct sockaddr
int main(int argc,char **argv)
{

   if(argc!=2)
   {
       printf("usage: tcpcli <IPaddress>");
       return 0;
   }
   struct  sockaddr_in  servaddr;
   int   sockfd[num],i;
    FILE *fp;
   bzero(&servaddr,sizeof(servaddr));
   servaddr.sin_family=AF_INET;
   servaddr.sin_port=htons(SERV_PORT);
   if(inet_pton(AF_INET,argv[1],&servaddr.sin_addr)<=0)
   {
        printf("inet_pton error\n");
        return 0;
   }
//  for(i=0;i<num;i++)
   {
  // fp=fopen("./test.temp","r");
   if((sockfd[i]=socket(AF_INET,SOCK_STREAM,0))<0)
   {
        printf("socket error\n");
        return 0;
   }
   if(connect(sockfd[i],(SA*)&servaddr,sizeof(servaddr))<0)
   {
        printf("connect error\n");
        return 0;
   }
//  shutdown(sockfd[i],2);
  close(sockfd[i]);
  char* ptr = malloc(3);
  int ret = read(sockfd[i], ptr, 2);
  // fclose(fp);
  printf("%d\n",i);
   }

      
   return 0;
}
