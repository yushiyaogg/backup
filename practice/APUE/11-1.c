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

pthread_t ntid;

void printids(const char *s)
{
    pid_t pid;
    pthread_t tid;

    pid = getpid();
    tid = pthread_self();
    printf("%s pid %u tid %u(0x%x)\n",s,(unsigned int)pid,(unsigned int )tid,(unsigned int)tid);
}

void* thr_fn(void* arg)
{
    printids("new thread:");
    return ((void*) 0);
}

int main(void)
{
    int err;
    err = pthread_create(&ntid, NULL,thr_fn,NULL);
    if(err != 0)
        printf("can't create thread: %s\n", strerror(err));
    printids("main thread:");
    sleep(1);
    exit(0);
}
