#ifndef _QUEUE_CPP_
#define _QUEUE_CPP_
#include <iostream>
#include "binary_search_tree.h"
#include "queue.h"
using namespace std;


Queue::Queue(int size)
    {
        this->size = size;
        ptr =  new node[size + 1];
        head = 1;
        rear = 0;        

    }

Queue::~Queue()
    {
        delete[] ptr;
    }
bool Queue::enqueue(struct node num)
    {
        if ((head + 1) % size == rear)
            return false;
        else
        {
            *(ptr + head) = num;
            head = (head + 1) % size;
            return true;
        }
        
    }
bool Queue::dequeue(struct node* num)
    {
        if((rear + 1) % size == head)
            return false;
        else
        {
            rear = (rear + 1)%size;
            *num = *(ptr + rear);
            return true;
        }
    }

#endif
