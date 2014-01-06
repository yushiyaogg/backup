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
    int balance;
};
int right_rotate(struct node* &root)
{
    struct node* temp = root;
    root = root-> left_child;
    temp -> left_child = root-> right_child;
    root -> right_child = temp;
    root -> right_child -> balance = 0;
    root -> balance = 0;
    return 0;
}

int left_rotate(struct node* &root)
{
    struct node* temp = root;
    root = root -> right_child;
    temp -> right_child = root -> left_child;
    root -> left_child = temp;
    root -> left_child -> balance = 0;
    root -> balance = 0;
    return 0;
}
int d_left_rotate(struct node* &root)
{
    struct node* temp = root;
    root = root -> right_child;
    temp -> right_child = root -> left_child;
    root -> left_child = temp;
    root -> left_child -> balance = -1;
    root -> balance = 1;
    return 0;
}
int d_right_rotate(struct node* &root)
{
    struct node* temp = root;
    root = root -> left_child;
    temp -> left_child = root -> right_child;
    root -> right_child = temp;
    root -> right_child -> balance = 1;
    root -> balance = -1;
    return 0;
}
int left_right_rotate(struct node* &root)
{
    struct node* temp = root;
    root = root -> left_child-> right_child;
    temp -> left_child -> right_child = root-> left_child;
    root -> left_child = temp -> left_child;
    temp -> left_child = root -> right_child;
    root -> right_child = temp;
    if(root ->balance == 1)
    {
        root -> left_child -> balance = 0;
        root -> right_child -> balance = -1;
    }
    else
    {
        root -> left_child -> balance = 1;
        root -> right_child -> balance = 0; 
    }
    root -> balance = 0;
    return 0;
}

int right_left_rotate(struct node* &root)
{
    struct node* temp = root;
    root = root -> right_child ->left_child;
    temp -> right_child -> left_child = root -> right_child;
    root -> right_child = temp ->right_child;
    temp -> right_child = root ->left_child;
    root -> left_child = temp;
    if(root -> balance == -1)
    {
        root -> left_child -> balance = 1;
        root -> right_child -> balance = 0;
    }
    else
    {
        root -> left_child -> balance = 0;
        root -> right_child -> balance = -1;
    }
    root -> balance = 0;
    return 0;
}
int add_value(int value,struct node* &root)
{
    if(root == NULL)
    {
        root =  new(struct node);
        root -> value = value;
        root -> left_child = NULL;
        root -> right_child = NULL;
        root -> balance = 0;
        return 1;
    }
    if(value < root -> value)
    {
        int ret;
        if((ret = add_value(value,root ->left_child)) == 0)
        {
            return 0;
        }
        else if(ret ==  1)
        {
            if(root -> balance == 0)
            {
                root -> balance = 1;
                return 1;
            }
            else if(root -> balance == -1)
            {
                root -> balance = 0;
                return 0;
            }
            else if(root -> balance == 1)
            {
                if(root -> left_child-> balance == 1)
                {
                    right_rotate(root);
                    return 0;
                }
                else if(root -> left_child -> balance == -1)
                {
                    left_right_rotate(root);
                    return 1;
                }
            }
        }
        else
        {
            cout << "error return value"<<endl;
            return -1;
        }
        
        
    }
    else if(value > root -> value)
    {
        int ret;
        if((ret = add_value(value,root -> right_child)) == 0)
        {
            return 0;
        }
        else if(ret ==  1)
        {
            if(root -> balance == 0)
            {
                root -> balance = -1;
                return 1;
            }
            else if(root -> balance == 1)
            {
                root -> balance = 0;
                return 0;
            }
            else if(root -> balance == -1)
            {
                if(root -> right_child-> balance == -1)
                {
                    left_rotate(root);
                    return 0;
                }
                else if(root -> right_child -> balance == 1)
                {
                    right_left_rotate(root);
                    return 1;
                }
            }
        }
        else
        {
            cout << "error return value"<<endl;
            return -1;
        }
        
        
    }
    else
    {
        cout << "the tree has already had the number"<< endl;
        return -1;
    }

}

int delete_value(int value,struct node* &root)
{
    if(root == NULL)
    {
        cout <<"no such number"<<endl;
        return -1;
    }
    if(value < root -> value)
    {
        int ret;
        if((ret = delete_value(value, root -> left_child)) == 0)
        {
            return 0;
        }
        else if(ret == 1)
        {
            if(root -> balance == -1)
            {
                if(root -> right_child -> balance == -1)
                {
                    left_rotate(root);
                    return 1;
                }
                else if(root -> right_child -> balance == 0)
                {
                    d_left_rotate(root);
                    return 0;
                }
                else if(root -> right_child -> balance == 1)
                {
                    right_left_rotate(root);
                    return 1; 
                }
            }
            else if(root -> balance == 0)
            {
                root -> balance = -1;
                return 0;
            }

            else if(root -> balance == 1)
            {
                root -> balance = 0;
                return 1;
            }
            else
            {
                cout << "balance number error"<<endl;
                return -1;
            }
        }
        else
        {
            cout << "error ret"<<endl;
            return -1;
        }
    }
    else if(value > root -> value)
    {
        int ret;
        if((ret = delete_value(value,root -> right_child)) == 0)
        {
            return 0;
        }
        else if(ret == 1)
        {
            if(root -> balance == -1)
            {
                root -> balance = 0;
                return 1;
            }
            else if(root -> balance == 0)
            {
                root -> balance = 1;
                return 0;
            }
            else if(root -> balance == 1)
            {
                if(root -> left_child -> balance == 0)
                {
                    d_right_rotate(root);
                    return 0;
                }
                else if(root -> left_child -> balance == 1)
                {
                    right_rotate(root);
                    return 1;
                }
                else if(root -> left_child -> balance == -1)
                {
                    left_right_rotate(root);
                    return 1;
                }
                else
                {
                    cout << "balance error number"<<endl;
                    return -1;
                }
            }
            else
            {
                cout << "balance error number"<<endl;
                return -1;
            }
        }
        else
        {
            cout << "error ret number"<< endl;
            return -1;
        }
    }
    else if(value == root -> value)
    {
    
        if(root -> left_child == NULL&&root -> right_child == NULL)
        {
            delete(root);
            root = NULL;
            return 1;
        }
        else if(root -> left_child == NULL||root -> right_child == NULL)
        {
            if(root -> left_child==NULL)
            {
                struct node* temp;
                temp = root;
                root = root -> right_child;
                delete temp;
                return 1;
            }
            else
            {
                struct node* temp;
                temp = root;
                root = root -> left_child;
                delete temp;
                return 1;
            }
        }
        else
        {
            struct node* temp1;
            int temp_ret;
            int temp_value;
            temp1 = root -> left_child;
            while(temp1 -> right_child != NULL)
            {
                temp1 = temp1 -> right_child;
            }
            temp_value = temp1->value;
            temp1 = root;
            temp_ret = delete_value(temp_value,root);
            temp1 ->value= temp_value;
            return temp_ret;
          /*  else if(temp_ret == 1)
            {
                root ->value = temp_value;
                if(root -> balance == 0)
                {
                    root -> balance = -1;
                    return 0;
                }
                else if(root -> balance == 1)
                {
                    root -> balance = 0;
                    return 1;
                }
                else if(root -> balance == -1)
                {
                    left_rotate(root);
                    return 1;
                }
            }*/

        }
    }
}

int main()
{
    struct node* ptr = NULL;
    add_value(50,ptr);
    add_value(40,ptr);
    add_value(30,ptr);
    add_value(20,ptr);
    add_value(10,ptr);
    add_value(35,ptr);
    add_value(25,ptr);
    add_value(27,ptr);
    delete_value(10,ptr);
    delete_value(50,ptr);
    delete_value(40,ptr);
    delete_value(30,ptr);
    delete_value(20,ptr);
    delete_value(10,ptr);
    return 0;

    
}
