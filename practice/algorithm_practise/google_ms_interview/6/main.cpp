///////////////////////////////////////////////////////////
//verify whether a sequence of number are the post order
//traversal of a  binary search tree(BST)
//Input: squence - the squence of intergers
//       length  - the length of squence
//Output: return true if the  squence is traversal  result of
//BST,otherwise return false
////////////////////////////////////////////////////////////
//
//
#include <iostream>
using namespace std;

bool verifySquenceofBST(int* ptr, int length)
{
    int *rear = ptr + length - 1;
    int *left_tree_ptr = ptr;
    int left_tree_length = 0;
    int *right_tree_ptr = NULL;
    int right_tree_length = 0;
    int mark = 0;//0 - search left tree  1 - search right tree
    if(length < 3)
        return true;
    while(ptr < rear)
    {
        if(*ptr < *rear)
        {
            if(mark == 1)
                return false;
            left_tree_length ++;
            ptr++;
        }
        else if (*ptr == *rear)
            return false;
        else
        {
            mark = 1;
            right_tree_length ++;
            ptr ++;
        }
    }
    right_tree_ptr = rear - right_tree_length;
    bool left_result = verifySquenceofBST(left_tree_ptr,left_tree_length);
    bool right_result = verifySquenceofBST(right_tree_ptr,right_tree_length);
    if(left_result == true&& right_result == true)
        return true;
    else
        return false;

}


int main()
{
    int length = 0;
    int num[] = {7,4,6,5};
    length = sizeof(num)/sizeof(int) ;
    cout << "length is "<<length<<endl;
    if(verifySquenceofBST(num,length) == true)
        cout << "this sequence is a post order traversal of a BST"<<endl;
    else
        cout << "this sequence is not a pst order traversal of a BST"<<endl;

        }
