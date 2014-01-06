#include <iostream>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <aio.h>
#include <unistd.h>

#define BUFSIZE 1024
using namespace std;
/*
*异步读写方式测试
*编译时，加入-lrt
*/
int main()
{
int fd,ret;
struct aiocb my_aiocb;
fd = open("testP.cpp",O_RDONLY);
if(fd<0) {
	cerr<<"open the file error:"<<strerror(errno)<<endl;
	return -1;
}
bzero((char*)&my_aiocb,sizeof(struct aiocb));
my_aiocb.aio_buf = malloc(BUFSIZE+1);
my_aiocb.aio_fildes = fd;
my_aiocb.aio_offset = 0;
my_aiocb.aio_nbytes = BUFSIZE;
ret = aio_read(&my_aiocb);
if(ret<0) cerr<<"aio read error:"<<strerror(errno)<<endl;
while(aio_error(&my_aiocb)==EINPROGRESS) ;//等待其完成读写
	if((ret=aio_return(&my_aiocb))<0){
		cerr<<"return "<<ret<<"read fail:"<<strerror(errno)<<endl;
	}
	else
	{	
		char*p=(char*)my_aiocb.aio_buf;
		cout<<"ret:"<<ret<<p<<endl;	
		free(p);
	}
	return 0;
}
