#ifndef _QUEUE_H_
#define _QUEUE_H_
#include "binary_search_tree.h"
class Queue
{
    public:
        int size;
        struct node* ptr;
        int head;
        int rear;

        Queue(int);
        ~Queue();
        bool enqueue(struct node num);
        bool dequeue(struct node* num);
};
#endif
