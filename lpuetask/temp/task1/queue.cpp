/*
 * =====================================================================================
 *
 *       Filename:  queue.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/13/12 01:15:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (), 
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#include "queue.h"

queue::queue()
{
    head = NULL;
    rear = NULL;    
}
int queue::enqueue(struct node* temp_node)
{
    struct queue_node* temp_queuenode;
    if((temp_queuenode = new(struct queue_node)) == NULL)
    {
        cout << "new queue_node error"<<endl;
        return -1;
    }
    temp_queuenode -> tree_node = temp_node;
    temp_queuenode -> next_queuenode == NULL;
    if(rear != NULL)
    {
        rear -> next_queuenode = temp_queuenode;
        rear = temp_queuenode;
    }
    else
    {
        rear = temp_queuenode;
        head = temp_queuenode;
    }
    return 0;
}
struct node* queue::dequeue()
{
    if(head == NULL)
        return NULL;
    else
    {
        struct node* temp_node;
        struct queue_node* temp_queuenode;
        temp_node = head -> tree_node;
        temp_queuenode = head -> next_queuenode;
        delete(head);
        head = temp_queuenode;
        if(head == NULL)
            rear = NULL;
        return temp_node;

    }
}
int queue::delete_queue()
{
    while( dequeue()!=NULL)
        ;    
    return 1;
}
