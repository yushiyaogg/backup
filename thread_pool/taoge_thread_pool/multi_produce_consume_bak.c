#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/time.h>

#define QLEN 5000

int fd[2];
int emptypos = QLEN;
long produceNum = 0;
long consumeNum = 0;

struct element
{
	int flag;
	struct element *next;
};

struct queue
{
	struct element *head;
	struct element *tail;
};

struct queue myqueue;

int empty()
{
//	if((myqueue.head == myqueue.tail) && (myqueue.head == NULL))
		if(!myqueue.head || !myqueue.tail)
		return 1;
	else
		return 0;
}

int full()
{
	if(emptypos == 0)
		return 1;
	else
		return 0;
}

void push(struct element *product)
{
	if(empty())
	{
		myqueue.head = product;
		myqueue.tail = product;
		(myqueue.head)->next = NULL; //product->next = NULL;
		emptypos--;
	}
	else
	{   
		(myqueue.tail)->next = product;
		myqueue.tail = product;
		product = NULL;
		emptypos--;
	}
}

struct element* pop()
{
	if(empty())
	{
		return 	NULL;
	}
	else
	{
		struct element* tmp;
		tmp = myqueue.head;
		myqueue.head = (myqueue.head)->next;
		//if(!myqueue.head) myqueue.tail=NULL;
		tmp->next = NULL;
		emptypos++;
		return tmp;
	}
}

int initqueue(int queuelen)
{
	struct element *tmp = NULL;
	myqueue.head = NULL;
	myqueue.tail = NULL;
	for(int i = 0; i < queuelen; i++)
	{
		tmp = (struct element *)malloc(sizeof(struct element));
		if(NULL == tmp)
		{
			perror("malloc failed");
			exit(1);
		}
		tmp->flag = 1;
		tmp->next = NULL;
		push(tmp);
		tmp = NULL;
	}
	return 0;
}

pthread_cond_t preadyr = PTHREAD_COND_INITIALIZER;
pthread_cond_t preadyw = PTHREAD_COND_INITIALIZER;
pthread_mutex_t plock = PTHREAD_MUTEX_INITIALIZER;

void doproduce(struct element *tmp)
{
	tmp->flag = 1;
	tmp->next = NULL;
}

void *produce(void *arg)
{
	struct element *tmp = NULL;
	int n = 0;
	while(1)
	{
		//printf("fff\n");
		n = read(fd[0],&tmp,sizeof(struct element *));
		if(0 > n)
		{
			perror("read error");
			pthread_exit(NULL);
		}
		doproduce(tmp);
		produceNum++;
		printf("\tthread %u produce %ld\n",(unsigned int)pthread_self(),produceNum);
		pthread_mutex_lock(&plock);
		while(full())
		{
           pthread_cond_wait(&preadyw, &plock);
		}
		push(tmp);
		//printf("eee");
		pthread_mutex_unlock(&plock);
		pthread_cond_broadcast(&preadyr);
	}
}

void doconsume(struct element *tmp)
{
	tmp->flag = 0;
	tmp->next = NULL;
}

void *consume(void *arg)
{
	struct element *tmp = NULL;
	int n = 0;
	while(1)
	{
		//printf("dddd\n");
		tmp = NULL;
		pthread_mutex_lock(&plock);
		while(empty())
		{
			pthread_cond_wait(&preadyr, &plock);
		}
		tmp = pop();
		pthread_mutex_unlock(&plock);
		pthread_cond_broadcast(&preadyw);
		doconsume(tmp);
		consumeNum++;
	    //printf("\tthread %u consume %ld\n",(unsigned int)pthread_self(),consumeNum);
		n = write(fd[1], &tmp, sizeof(struct element*));
		//printf("eeee\n");
		if(0 > n)
		{
			perror("write pipe error");
			pthread_exit(NULL);
		}
	}
}

int main(int argc,char *argv[])
{
	if(argc < 4)
	{
		printf("usage:%s producerNum, consumerNum, runtime\n",argv[0]);
		exit(1);
	}
	int runtime = atoi(argv[3]);
	printf("aaaa\n");
	//initqueue(atoi(argv[3]));
	initqueue(QLEN);
	if(pipe(fd) < 0) //create pipe
	{
		perror("pipe error");
		exit(1);
	}
	for(int i = 0; i < atoi(argv[1]); i++)
	{
		pthread_t protid;
		if(0 != pthread_create(&protid, NULL, produce, NULL))
		{
			perror("can't create producer thread");
			exit(1);
		}
		if(0 != pthread_detach(protid))
		{
			perror("detach error");
			exit(1);
		}
	}
	printf("bbbbbbbbb\n");
	for(int j = 0; j < atoi(argv[2]); j++)
	{
		pthread_t contid;
		if(0 != pthread_create(&contid, NULL, consume, NULL))
		{
			perror("can't create consumer thread");
			exit(1);
		}
		if(0 != pthread_detach(contid))
		{
			perror("detach error");
			exit(1);
		}
	}
	printf("cccccccc\n");
	sleep(runtime);
	printf("produceNum = %ld, producerate = %ld\n", produceNum, produceNum/runtime);
	printf("consumeNum = %ld, consumerate = %ld\n", consumeNum, consumeNum/runtime);
	return 0;
}










