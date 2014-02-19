#include <iostream>
#include <stack>

using namespace std;

int IsPossiblePopOrder(int* pPush, int* pPop, int length)
{
    int Pushoffset = 0;
    int Popoffset  = 0;
    if(length <= 0)
        return -1;
    stack <int> temp_stack;
    for(; Popoffset < length; Popoffset++)
    {
        while(temp_stack.size() == 0||temp_stack.top() != *(pPop + Popoffset))
        {
            if(Pushoffset >= length)
                return -1;
            temp_stack.push(*(pPush+Pushoffset));
            Pushoffset ++;
        }
        temp_stack.pop();

    }
    return 0;
}

int main()
{
    int Push[] = {1,2,3,4,5};
    int Pop[]  = {5,4,3,2,46};
    int *pPush = Push;
    int *pPop = Pop;
    int length = sizeof(Push)/sizeof(int);
    cout << IsPossiblePopOrder(pPush,pPop,length)<<endl;
}
