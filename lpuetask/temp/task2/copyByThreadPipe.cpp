/*
 * =====================================================================================
 *
 *       Filename:  copyByThreadPipe.cpp
 *
 *    Description:  ���߳̿����ļ�
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

int fdSource,fdDest;//Դ�ļ���Ŀ���ļ�������
int fd[2];//�ܵ��ļ�������
struct stat buf;
//��Ҫ������ܵ������ݽṹ
struct dataDelieve
{
    //�ļ�ƫ����
    off_t offset;
    //�ÿ�������׵�ַ
    char *ptr;
    //�����ֽ���
    int bytes;
};


//��Դ�ļ��ж�ȡƫ���������ݵ�ַ�������ֽڵ��ܵ����߳�
void * readDataToPipe(void *arg)
{

    //��֮ǰ�ļ�ƫ�������Լ���Ƿ񵽴��ļ�ĩβ
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
        //�����ļ�ĩβ��
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

//�ӹܵ��ļ���ȡ���ݵĵ�ַ���ļ�ƫ������Ŀ���ļ����߳�
void * readPipeToDest(void *arg)
{
    //�ӹܵ��ж�ȡ���ݣ��ļ�ƫ�����������׵�ַ�������ֽ�����
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
    //���������в���������argv[1]ΪԴ�ļ���argv[2]ΪĿ���ļ�
    if(argc != 3)
    {
        printf("arguments are't three\n");
        exit(1);
    }

    //����Դ�ļ��Ƿ����,���ھʹ򿪻�ȡ�ļ�������
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
    //��ȡĿ���ļ��ļ�������
    if((fdDest=open(argv[2],O_RDWR | O_TRUNC | O_CREAT,buf.st_mode)) < 0)
    {
        printf("open %s error\n",argv[2]);
        exit(1);
    }

    //�����ܵ�
    if(pipe(fd) < 0)
    {
        printf("create pipe error\n");
        exit(1);
    }

    //��Դ�ļ��ж����ݺ�ƫ�������ܵ����߳�
    int errR;
    pthread_t tidR;
    errR = pthread_create(&tidR,NULL,readDataToPipe,NULL);
    if(errR != 0)
    {
        printf("create read thread error:%s\n",strerror(errR));
        exit(1);
    }

    //�ӹܵ��ж�ȡ���ݵ�Ŀ���ļ��е��߳�
    
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
