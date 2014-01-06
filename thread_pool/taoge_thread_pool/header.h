#ifndef __HEADER_H_
#define __HEADER_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <pthread.h>
//C++ 头文件
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>

using namespace std;
#define PORT 8887
#define BACKLOG 10000
#define MAXLINE 512
#define BUFFERSIZE (MAXLINE+sizeof(size_t)+1)
#define SPORT PORT //服务器端口

//定义操作命令
enum _aio_request_type
{
_AIO_READ=0,
_AIO_WRITE,
_AIO_OPEN,
_AIO_CLOSE,
_AIO_CANCEL
};
typedef _aio_request_type aio_request_t;

//operation status
enum _aio_request_status
{
_AIO_STATUS_SUBMIT=0,
_AIO_STATUS_OK,
_AIO_STATUS_FAIL,
_AIO_STATUS_CANCEL
};
typedef _aio_request_status aio_request_status;
//operation after return
struct _aio_ret_t
{
int aio_return;
int aio_errno;
pthread_t tid;
unsigned int  data;
void* _retdata;
};
typedef struct _aio_ret_t aio_ret_t;

struct pipeset
{
unsigned int in; //输入数据的管道
unsigned int out;//输出反馈结果的管道
};
//发送请求的定义
struct req_t
{
aio_request_t req_op; //操作类型，读，写
int fd;	
size_t count;
off_t offset;
char* data;//缓冲数据地址
aio_request_status status;//操作状态
aio_ret_t *ret;
int rid;//请求id
};

struct tagHead
{
size_t length;
char *msg;
};

#endif
