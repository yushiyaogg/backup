#include <iostream>
using namespace std;

int reverse(char* ptr, int length)
{
    if(ptr == NULL)
        return -1;
    char temp;
    int middle = length / 2;
    for(int i = 0 ; i < middle; i ++)
    {
        temp = *(ptr + i);
        *(ptr + i ) = *(ptr + length -i -1);
        *(ptr + length - i - 1) = temp;
    }
    return 0;
}

int left_rotate(char* ptr, int length, int offset)
{
    if(offset > length) 
        return -1;
    else
    {
        reverse(ptr, offset);
        reverse(ptr+offset, length - offset);
        reverse(ptr, length);
        return 0;
    }
}

int main()
{
    char string[] =  "abcdefghijklmn";
    int length = sizeof(string) -1;
    char *ptr = string;
    left_rotate(ptr,length, 14);
    cout <<string <<endl;
}
