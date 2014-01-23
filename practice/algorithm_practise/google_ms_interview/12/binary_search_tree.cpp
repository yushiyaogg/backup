#ifndef _BINARY_SEARCH_TREE_CPP_
#define _BINARY_SEARCH_TREE_CPP_
#include <iostream>
#include "queue.h"
#include "binary_search_tree.h"
using namespace std;




Binary_Search_Tree::Binary_Search_Tree()
        {
            root = NULL;
            queue = new Queue(100);
        }

        Binary_Search_Tree::~Binary_Search_Tree()
        {
            delete_this(this-> root);
        }


        int Binary_Search_Tree::insert_node(int num)
        {
            return addnum(num,this -> root);
        }
        
        int Binary_Search_Tree::level_traversal()
        {
            struct node num;
            if(root == NULL)
                return 0;
            else
            {
                queue->enqueue(*root);
            }
            while( queue->dequeue(&num) == true)
            {
                cout <<num. num<<endl;
                if(num.leftchild != NULL)
                    queue -> enqueue(*num.leftchild);
                if(num.rightchild != NULL)
                    queue -> enqueue(*num.rightchild);

            }
        }


        int Binary_Search_Tree::delete_this(struct node* &root)
        {
            if(root -> leftchild != NULL)
                delete_this(root -> leftchild);
            else if(root -> rightchild != NULL)
                delete_this(root -> rightchild);
            else
            {
                delete root;
                return 0;
            }
        }
        int Binary_Search_Tree::addnum(int num, struct node* &root)
        {
            if(root != NULL)
            {
                if(num == root-> num)
                    return -1;
                else if(num > root->num)
                {
                    return addnum(num,root -> rightchild);
                }
                else
                    return addnum(num,root -> leftchild);
            }
            root = new struct node;
            root -> num = num;
            root -> leftchild = root -> rightchild = NULL;
        
        }

#endif
