#ifndef _BINARY_SEARCH_TREE_H_
#define _BINARY_SEARCH_TREE_H_
#include "queue.h"
struct node
  {
       int num;
       struct node* leftchild;
       struct node* rightchild;
  };
 class Binary_Search_Tree
{
    public:
        node *root;
        class Queue* queue;

        Binary_Search_Tree();
        ~Binary_Search_Tree();
        int insert_node(int num);
        int level_traversal();
        int delete_this(struct node* &root);
        int addnum(int num, struct node* &root);
  };
#endif
