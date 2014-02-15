#include <iostream>
#include <math.h>
using namespace std;
const int MAX_INT = 2147483647;
const int MIN_INT = -2147483648;
int Str2Int(char* ptr, int length, int &number)
{
    long num = 0;
    int  i = 0;
    bool minus = false;
    if(ptr == NULL||length > 11)
        return -1;
    if(*ptr == '-')
    {
        minus = true;
        i ++;
    }
    else if(*ptr == '+')
    {
        i ++;
    }
    else if(*ptr < '0'|| *ptr > '9')
        return -2;

    for( ; i < length ; i ++)
    {
        if(*(ptr+i) < '0'||*(ptr+i) > '9')
            return -2;
        else
        {
            num = num * 10 + (*(ptr+i) - '0');
        }
        
    }
    if(minus == false)
    {
        if(num > MAX_INT)
            return -3;
        else
        {
            number = int(num);
            return 0;
        }

    }
    else if(minus == true)
    {
        num = 0 - num;
        if(num < MIN_INT)
            return -3;
        else
        {
            number = int(num);
            return 0;
        }
    }
}

int main()
{
    char string[] = "-1333332423";
    char *ptr = string;
    int  length = sizeof(string) -1;
    int number = 0;
    if(Str2Int(ptr, length, number) < 0)
        cout <<"error"<<endl;
    else
        cout << number <<endl;
}
