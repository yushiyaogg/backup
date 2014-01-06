#include "aio.h"
#include "header.h"


static inline ssize_t do_read(int,void*,size_t,off_t);
static inline ssize_t do_write(int,void*,size_t,off_t);
static inline int do_open(char*,int,mode_t);
static inline int do_close(int);
//C++不允许乱序赋值,C语言可以
static const struct aio_ops aop = 
{
do_read,
do_write,
do_open,
do_close,
};

ssize_t aio_read(int fd,void*buf,size_t count,off_t offset)
{
	return aop.io_read(fd,buf,count,offset);
}

ssize_t aio_write(int fd,void* buf,size_t count,off_t offset)
{
	return	aop.io_write(fd,buf,count,offset);

}
int aio_open(char*path,int flag,mode_t mode)
{
	return aop.io_open(path,flag,mode);
}
int aio_close(int fd)
{
	return aop.io_close(fd);
}
//多线程读写的底层函数 性能没有明显提升,瓶颈不在磁盘上面 
static inline ssize_t do_read(int fd,void* buf,size_t count,off_t offset)
{    
    int len;
    char s[]="Hello,World";
    len = strlen(s);
    memcpy(buf,s,len);
    return len;
//	return pread(fd,buf,count,offset);
}

static inline ssize_t do_write(int fd,void* buf,size_t count,off_t offset)
{
	return pwrite(fd,buf,count,offset);
}
static inline int do_open(char*path,int flag,mode_t mode)
{
	if(flag&O_CREAT)
	return open(path,flag,mode);
	return open(path,flag);
}
static inline int do_close(int fd)
{
	return close(fd);
}
