/*
 * =====================================================================================
 *
 *       Filename:  head.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/13/12 00:52:32
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (), 
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#ifndef _HEAD_H_
#define _HEAD_H_
#include <iostream>
const int child_num = 10;
const int tree_height = 3;
using namespace std;
struct node{
    char *content;
    int  content_len;
    struct node* children[child_num];
};
struct queue_node{
    struct node* tree_node;
    struct queue_node* next_queuenode;
};
#endif
