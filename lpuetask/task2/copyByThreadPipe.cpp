/*
 * =====================================================================================
 *
 *       Filename:  copyByThreadPipe.cpp
 *
 *    Description:  多线程拷贝文件
 *
 *        Version:  1.0
 *        Created:  02/15/12 09:26:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:    
 *        Company:  NDSL UESTC
 *
 * =====================================================================================
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <iostream>
using namespace std;
#define BUFSIZE 4096
#define WRITETHREADNUM 2

int fdSource,fdDest;//源文件、目的文件描述符
int fd[2];//管道文件描述符
struct stat buf;
//需要传输给管道的数据结构
struct dataDelieve
{
    //文件偏移量
    off_t offset;
    //该块的数据首地址
    char *ptr;
    //数据字节数
    int bytes;
};


//从源文件中读取偏移量、数据地址、数据字节到管道的线程
void * readDataToPipe(void *arg)
{

    //读之前文件偏移量，以检测是否到达文件末尾
    off_t offs;
    int flagEnd=0;

    while(!flagEnd)
    {
        char *dataAddr = (char *)malloc(BUFSIZE);
        if((offs = lseek(fdSource,0,SEEK_CUR)) < 0)
        {
            printf("lseek error\n");
            return ((void *) 1);
        }

        int n = read(fdSource,dataAddr,BUFSIZE);
        //读到文件末尾了
        if(n == 0 )
        {
            flagEnd = 1;
            close(fd[1]);
            close(fdSource);
            return ((void *) 0);
        }
        else if(n < 0)
        {
            printf("read data from source file error\n");
            return ((void *) 1 );
        }
        else 
        {    
        struct dataDelieve data = {offs,dataAddr,n};
       // printf("***********************read data from source:***************\n%s\noffset:%d\nbytes:%d\n",dataAddr,offs,n);
        write(fd[1],&data,sizeof(struct dataDelieve));
        }
    }
}

//从管道文件读取数据的地址和文件偏移量到目的文件的线程
void * readPipeToDest(void *arg)
{
    //从管道中读取数据（文件偏移量、数据首地址、数据字节数）
    struct dataDelieve data;
//    printf("size of off_t:%d\nint:%d\nchar*:%d\n",sizeof(off_t),sizeof(int),sizeof(char*));
//    printf("size of struct:%d\n",sizeof(data));
    int n;
    while((n = read(fd[0],&data,sizeof(struct dataDelieve)) > 0))
    {
        int nWrite;
        nWrite = pwrite(fdDest,data.ptr,data.bytes,data.offset);
        if(nWrite <= 0)
        {
            printf("write data to dest error\n");
            return ((void *) 1 );
        }
        else
        {
           // printf("************************write data to dest:\n%s\noffset:%d\nbytes:%d\n",data.ptr,data.offset,data.bytes);
            free(data.ptr);
        }
    }

    if(n == 0)
    {
        printf("copy complete\n");
        close(fd[0]);
        close(fdDest);
        return ((void *) 0 );
    }
    else if(n < 0)
    {
        printf("read data from pipe error\n");
        return ((void *) 1 );
    }
           
}

int main(int argc,char *argv[])
{
    struct timeval start_time,end_time;
    //测试命令行参数个数，argv[1]为源文件，argv[2]为目的文件
    if(argc != 3)
    {
        printf("arguments are't three\n");
        exit(1);
    }

    //测试源文件是否存在,存在就打开获取文件描述符
    if(access(argv[1],F_OK) == 0)
    {
        if(lstat(argv[1],&buf) < 0)
        {
            printf("lstat %s error\n",argv[1]);
            exit(1);
        }
        if((fdSource=open(argv[1],O_RDONLY)) < 0)
        {
            printf("open %s error\n",argv[1]);
            exit(1);
        }
    }
    gettimeofday(&start_time,NULL);
    //获取目的文件文件描述符
    if((fdDest=open(argv[2],O_RDWR | O_TRUNC | O_CREAT,buf.st_mode)) < 0)
    {
        printf("open %s error\n",argv[2]);
        exit(1);
    }

    //创建管道
    if(pipe(fd) < 0)
    {
        printf("create pipe error\n");
        exit(1);
    }

    //从源文件中读数据和偏移量到管道的线程
    int errR;
    pthread_t tidR;
    errR = pthread_create(&tidR,NULL,readDataToPipe,NULL);
    if(errR != 0)
    {
        printf("create read thread error:%s\n",strerror(errR));
        exit(1);
    }

    //从管道中读取数据到目的文件中的线程
    
    pthread_t tidW[WRITETHREADNUM];   
    for(int i=0;i<WRITETHREADNUM;++i)
    {
        int errW;
        errW = pthread_create(&tidW[i],NULL,readPipeToDest,NULL);
        if(errW != 0)
        {
            printf("create write thread %d error:%s\n",i,strerror(errW));
            exit(1);
        }
    }

    pthread_join(tidR,NULL);

    for(int i=0;i<WRITETHREADNUM;++i)
    {
        pthread_join(tidW[i],NULL);
    }
    gettimeofday(&end_time,NULL);
    cout <<"the time of copy the file is:" <<end_time.tv_sec - start_time.tv_sec << "s"<< end_time.tv_usec -start_time.tv_usec << "us"<<endl;

    exit(0);
}
