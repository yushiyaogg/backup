/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/13/12 04:31:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (), 
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#include "head.h"
#include "queue.h"
#include <fcntl.h>
#include <string.h>
#include <sys/time.h>
struct node* create_tree(int layer)
{
    if(layer == 0)
        return NULL;
    else
    {
        struct node *temp = new(struct node);
        temp-> content_len = 3;
        temp-> content = new char[3];
        memcpy(temp-> content,"aaa", 3);
        for(int i = 0; i<=9;i ++)
        {
            temp-> children[i]=create_tree(layer -1);
        }
        return temp;
    }
    
}
int store(struct node *root)
{
    int fd;
    class queue* queue1 = new queue();
    struct node* temp;
    queue1 -> enqueue(root);
    if((fd = open("store", O_WRONLY)) < 0)
    {
        cout << "open error"<<endl;
        return -1;
    }
    while(queue1->head != NULL)
    {
        temp = queue1->dequeue();
        for(int i = 0;i<=9; i++)
        {
            if(temp-> children[i]!= NULL)
                queue1->enqueue(temp-> children[i]);
        }
        if(write(fd, (char*)(&(temp -> content_len)),4) !=  4)
        {
            cout << "write len error"<<endl;
            return -1;
        }
        if(write(fd,temp-> content,temp->content_len) != temp->content_len)
        {
            cout << "write content error"<<endl;
            return -1;
        }
    }
    close(fd);
    return 0;
}
struct node* rebuild()
{
    class queue* queue1 = new queue();
    char readbuff[20];
    struct node* root;
    root = new (struct node);
    queue1->enqueue(root);
    struct node* re_root;
    char *ptr = readbuff;
    int len;
    int count_child = 9;
    int fd;
    if((fd = open("store",O_RDONLY)) < 0)
    {
        cout << "open error"<<endl;
        return NULL;
    }


////////////////////////////////////////////////
        if((read(fd,(char*)(&len),4)) ==0)
        {
            cout <<"empty file"<<endl;
            return NULL;
        }
        if(len != 0)
        {
            if((read(fd, ptr, len)) != len)
            {
                cout << "error file"<<endl;
                return NULL;
            }
        }
        if(len == 0)
        {
            cout <<"error file"<<endl;
            return NULL;
        }
        else
        {
            re_root = root;
            re_root ->content_len = len;
            re_root -> content = new char[len];
            memcpy(re_root->content,ptr,len);
        }
////////////////////////////////////////////////////////////////////////first node



    while(1)
    {
        if(count_child > 9)
        {
            count_child = 0;
            re_root = queue1->dequeue();
        }
        
        if((read(fd,(char*)(&len),4)) ==0)
            break;
        if(len != 0)
        {
            if((read(fd, ptr, len)) != len)
            {
                cout << "read error"<<endl;
                break;
            }
        }
        if(len == 0)
        {
            re_root -> children[count_child] == NULL;
            count_child ++;
        }
        else
        {
            re_root-> children[count_child] = new(struct node);
            re_root -> children[count_child]->content_len = len;
            re_root -> children[count_child]-> content = new char[len];
            memcpy(re_root-> children[count_child]->content,ptr,len);
            queue1->enqueue(re_root -> children[count_child]);
            count_child ++;
        }
        


    }
    queue1->delete_queue();
    return root;
}
int main(int argc, char **argv)
{
    struct timeval start_time, end_time;
    struct node* root;
    root = create_tree(7);
    gettimeofday(&start_time,NULL);
    store(root);
    gettimeofday(&end_time,NULL);
    cout <<"the time of store the tree is:" <<end_time.tv_sec - start_time.tv_sec << "s"<< end_time.tv_usec -start_time.tv_usec << "us"<<endl;

    gettimeofday(&start_time,NULL);
    root = rebuild();
    gettimeofday(&end_time,NULL);
    cout <<"the time of rebuild the tree is:" <<end_time.tv_sec - start_time.tv_sec << "s"<< end_time.tv_usec -start_time.tv_usec << "us"<<endl;
    return 1;
}
