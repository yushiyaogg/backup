/*
 * =====================================================================================
 *
 *       Filename:  Fibonacci.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/06/12 16:34:29
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

struct number
{
    int num;
    struct number* next;
};
int Fibonacci(int month)
{
    struct number number1,number2;
    number1.num = 0;
    number1.next = &number2;
    number2.num = 1;
    number2.next = &number1;
    struct number *ptr;
    ptr = &number1;
    for(int i = 0;i< month; i++)
    {
        cout << ptr ->num<<endl;
        ptr -> num = ptr->num + ptr -> next ->num;
        ptr = ptr -> next;
    }
    return 0;

}
int main()
{
    Fibonacci(20);
}
