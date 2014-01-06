#include "aio.h"
#include <stdio.h>

static int do_read(struct req_t*);
static int do_write(struct req_t*);

static const struct aio_ops aop = 
{
.read     = 	do_read,
.write    =	do_write,
};

int aio_read(struct req_t *req)
{
	aop.read(req);
	return 0;
}

int aio_write(struct req_t *req)
{
	aop.write(req);
	return 0;
}

static int do_read(struct req_t *req)
{
	printf("do_read function!\n");
	return 0;
}

static int do_write(struct req_t *req)
{
	printf("do_write function\n");
	return 0;
}
