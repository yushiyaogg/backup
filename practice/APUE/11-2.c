/*
 * =====================================================================================
 *
 *       Filename:  11-1.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/01/12 14:59:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdarg.h>

pthread_t tid2;

void* thr_fn1(void* arg)
{
    int err;
    void *tret;
    err = pthread_join(tid2,&tret);
    if(err != 0)
        printf("can't join with ptread 1 : %s\n",strerror(err));
    printf("thread 2 exit code %d\n",(long) tret);
    pthread_exit((void *)123);
}

void* thr_fn2(void* arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)123);
}

int main(void)
{
    int err;
    pthread_t tid1;
    void *tret;

    err= pthread_create(&tid1,NULL,thr_fn1,NULL);
    if(err != 0)
        printf("can't create thread 1: %s\n",strerror(err));
    
    err= pthread_create(&tid2,NULL,thr_fn2,NULL);
    if(err != 0)
        printf("can't create thread 1: %s\n",strerror(err));
    err = pthread_join(tid1, &tret);
    if(err != 0)
        printf("can't join with ptread 1: %s\n",strerror(err));
    
    printf("thread 2 exit code %d\n",(long) tret);
}

