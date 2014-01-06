/*
 * =====================================================================================
 *
 *       Filename:  Three_Color_Flag.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/09/12 21:16:30
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

void _swap(char* a,char* b)
{
    char temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
int three_color_flag(char* ptr, int len)
{
    char *head;
    char *rear;
    char *b ;
    char *w ;
    char *r ;
    head = ptr;
    rear = ptr + len - 2;
    b = w = head;
    r = rear;
    while(rear >= head)
    {
        if(*head == 'b')
        {
            _swap(head,w);
            w++;
            head ++;
        }
        else if(*head == 'w')
        {
            head ++;
        }
        else if(*head == 'r')
        {
            _swap(head,r);
            r --;
            rear --;
        }
    }
}

int main()
{
    char rwb[] = "rwbbbwrrrwbwrrww";
    char *ptr = rwb;
    cout << rwb<<endl;
    three_color_flag(ptr,sizeof(rwb));
    cout << rwb <<endl;
}
