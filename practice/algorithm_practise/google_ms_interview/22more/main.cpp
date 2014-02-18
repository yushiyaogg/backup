//left shift and right shift of number which description of char
//


#include <iostream>
using namespace std;

int left_shift(char* ptr)
{
    int flag = 0;
    if(ptr == NULL)
        return -1;
    while(*ptr != '\0')
    {
    switch(*ptr)
    {
    case '0': 
        if(flag)
        {
            *ptr = '5';
            flag = 0;
        }
        else
            *ptr = '0';
        ptr ++;
        continue;
     case '1':
        if(flag)
            *ptr = '5';
        else
        {
            *ptr = '0';
            flag = 1 ;
        }        
        ptr ++ ;
        continue;
     case '2':
        if(flag)
        {
            *ptr = '6';
            flag = 0 ;
        }
        else
            *ptr = '1';
        ptr ++;
        continue;
     case '3':
        if(flag)
            *ptr = '6';
        else
        {
            *ptr = '1';
            flag = 1;
        }
        ptr ++;
        continue;
     case '4':
        if(flag)
        {
            *ptr = '7';
            flag = 0;
        }
        else
            *ptr = '2';
        ptr ++;
        continue;
     case '5':
        if(flag)
            *ptr = '7';
        else
        {
            *ptr = '2';
            flag = 1;
        }
        ptr ++;
        continue;
     case '6':
        if(flag)
        {
            *ptr = '8';
            flag = 0;
        }
        else
            *ptr = '3';
        ptr ++;
        continue;
     case '7':
        if(flag)
            *ptr = '8';
        else
        {
            *ptr = '3';
            flag = 1;
        }
        ptr ++;
        continue;
     case '8':
        if(flag)
        {
           *ptr = '9';
           flag = 1;
        }
        else
           *ptr = '4';
        ptr ++;
        continue;
     case '9':
        if(flag)
            *ptr = '4';
        else
        {
            *ptr = '9';
            flag = 1;
        }
        ptr++;
        continue;
    }
      
    }   
             
    return 0; 
    
}

int main ()
{
    char num[] = "1423401347897";
    char *ptr = num;
    cout << num<<endl;
    if( left_shift(ptr) ==0)
        cout << num <<endl;
}
