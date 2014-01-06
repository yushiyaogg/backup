/*
 * =====================================================================================
 *
 *       Filename:  divide.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/19/12 19:56:37
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
int divide_and_merge(int *ptr, int len)
{
    int ptr1[len/2];
    int ptr2[len - len /2];
    int ptr1len = 0;
    int ptr2len = 0;
    if(len == 1)
        return 0;
    else
    {
        divide_and_merge(ptr,len/2 );
        divide_and_merge(ptr + len / 2, len - len /2);
        for(int i = 0; i < len /2; i ++)
            ptr1[i] = *(ptr + i);
        for(int i = 0; i < len - len/ 2; i ++)
            ptr2[i] = *(ptr + i + len /2);
        for(int i = 0 ; i < len ;i ++)
        {
            if(ptr1len == len /2)
            {
                for(int j = 0 ; j < len - len/2 - ptr2len; j ++)
                    *(ptr + i + j) = ptr2[ptr2len + j];
                break;
            }
            if(ptr2len == len - len /2)
            {
                for(int j = 0; j < len/2 - ptr1len; j ++)
                    *(ptr + i +j) = ptr1[ptr1len + j];
                break;
            }
            if((ptr1[ptr1len]) <= (ptr2[ptr2len]) )
            {
                *(ptr + i) = ptr1[ptr1len];
                ptr1len ++;
                continue;
            }
            if((ptr2[ptr2len]) < (ptr1[ptr1len]) )
            {
                *(ptr + i) = ptr2[ptr2len];
                ptr2len ++;
                continue;
            }
        }
        return 0;
    }
   
}
int main()
{
    int a[10] = {5,3,2,0,34,35,11,0,2,1};
    divide_and_merge(a,10);
    for(int i = 0; i < 10; i ++)
    {
        cout << "a" << i<<": "<<a[i]<<endl;
    }
    return 0;
}
