/*
 * =====================================================================================
 *
 *       Filename:  queue.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/13/12 01:02:49
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (), 
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#ifndef _QUEUE_H_
#define _QUEUE_H_
#include "head.h"
class queue
{
   public:
        struct queue_node* head;
        struct queue_node* rear;
        int enqueue(struct node*);
        struct node* dequeue();
        int delete_node();
        int delete_queue();
        queue();
};
#endif
