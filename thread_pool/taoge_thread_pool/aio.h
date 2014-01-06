/**处理异步调用函数处理***/
#ifndef _AIO_H_
#define _AIO_H_
#include <unistd.h>
#include <fcntl.h>

struct aio_ops 
{
ssize_t (*io_read)(int,void*,size_t,off_t);
ssize_t (*io_write)(int,void*,size_t,off_t);
int	(*io_open)(char*,int,mode_t);
int 	(*io_close)(int);
};

ssize_t aio_read(int,void*,size_t,off_t);
ssize_t aio_write(int,void*,size_t,off_t);
int  aio_open(char*,int,mode_t);
int  aio_close(int);
#endif
