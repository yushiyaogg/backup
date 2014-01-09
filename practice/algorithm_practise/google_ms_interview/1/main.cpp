/*
 * =====================================================================================
 *
 *       Filename:  balance_tree.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/06/12 00:28:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#include <iostream>
using namespace std;

struct node
{
    int value;
    struct node* left_child;
    struct node* right_child;
};

int add_value(int value,struct node* &root)
{
    if(root == NULL)
    {
        root =  new(struct node);
        root -> value = value;
        root -> left_child = NULL;
        root -> right_child = NULL;
        return 1;
    }
    if(value < root -> value)
    {
        add_value(value,root ->left_child);
       	return 1; 
        
    }
    else if(value > root -> value)
    {
       add_value(value,root -> right_child);
       return 1;
        
    }
    else
    {
        cout << "the tree has already had the number"<< endl;
        return -1;
    }

}

int conver_binary_ordertree_to_double_list(struct node* ptr,struct node* &listptr)
{
    if (ptr == NULL)
    {
        listptr = NULL;
        return 0;
    }
    if(ptr -> left_child != NULL)
    {
            conver_binary_ordertree_to_double_list(ptr -> left_child,listptr);
    }
        ptr -> left_child = listptr;
        if(listptr != NULL)
        {
            listptr -> right_child = ptr;
            listptr = listptr -> right_child;
        }
        else
            listptr = ptr;
    if(ptr -> right_child != NULL)
    {
            conver_binary_ordertree_to_double_list(ptr -> right_child,listptr);
    }
    return 0;
}

int main()
{
    struct node* ptr = NULL;
    struct node* listptr = NULL;
    add_value(30,ptr);
    add_value(10,ptr);
    add_value(50,ptr);
    add_value(5,ptr);
    add_value(25,ptr);
    add_value(20,ptr);
    add_value(40,ptr);
    add_value(27,ptr);
//    delete_value(10,ptr);
//    delete_value(50,ptr);
//    delete_value(40,ptr);
//    delete_value(30,ptr);
//    delete_value(20,ptr);
//    delete_value(10,ptr);
    conver_binary_ordertree_to_double_list(ptr,listptr);
    return 0;

    
}
