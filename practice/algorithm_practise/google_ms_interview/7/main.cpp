/////////////////////////////////////////////////////////////////
//reverse a senctence as an unit of word
//eg:input - I am a student  output:student a am I
//input :a string
//output: a string
////////////////////////////////////////////////////////////////
#include <iostream>
#include <string.h>
using namespace std;

class Stack
{
    public:
        char* top;
        char* bottom;
        int   size;
        Stack(int size)
        {
            this ->size = size;
            top = bottom = new char(size);
        }
        ~Stack()
        {
            delete[] bottom;
        }
        bool push(char* ptr)
        {
            if(top - bottom < size)
            {
                *top = *ptr;
                top ++;
                return true;
            }
            return false;
        }
        bool pop(char* ptr)
        {
            if(top == bottom)
                return false;
            else
            {
                top --;
                *ptr = * top;
                return true;
            }
        }
};

int reverse(char* s, int length)
{
    class Stack stack(100);
    char temp;
    char sentence[length];
    char* ptr = sentence;
    for(int i = length; i > 0; i --)
    {
        if(*(s + i -1) != ' ')
            stack.push(s+i-1);
        else
        {
            while(stack.top != stack.bottom)
            {
                stack.pop(&temp);
                *ptr = temp;
                ptr ++;
            }
            *ptr = ' ';
            ptr ++;
        }
    }
            while(stack.top != stack.bottom)
            {
                stack.pop(&temp);
                *ptr = temp;
                ptr ++;
            }
    memcpy(s,sentence,length);
}

int main()
{
    char sentence[]="You don't have any verified emails. We recommend verifying at least one email. ";
    char* ptr = sentence;
    cout << "originial sentence:"<<sentence<<endl;
    int length = sizeof(sentence);
    cout << "length"<<length<<endl;
    reverse(ptr,length-1);
    cout << "after reverse sentece:"<<sentence<<endl;
}
