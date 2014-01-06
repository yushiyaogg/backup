#include "header.h"

int main()
{
	aio_ret_t *p=new aio_ret_t;//16byte
	req_t *q= new req_t;//32byte
	req_t *q1 = (req_t*)malloc(sizeof(req_t));
	cout<<"p:"<<sizeof(*p)<<endl;
	cout<<"q:"<<sizeof(*q)<<endl;
	q->req_op = _AIO_READ;
	q->fd=0;
	q->count =1 ;
	q->offset = 1;
//	q->status = -1;
	q->rid = 1;
	struct tagHead *head = new struct tagHead;
	cout<<"head:"<<sizeof(*head)<<endl;
	cout<<"q1:"<<sizeof(*q1)<<endl;
	cout<<"enum:"<<sizeof(aio_request_t)<<endl;
	delete p;
	delete q;
	free(q1);
	return 0;
}
