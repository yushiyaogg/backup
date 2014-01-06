/*
 * =====================================================================================
 *
 *       Filename:  Hanoi.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/06/12 16:15:51
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


int Hanoi(int n,char a, char b, char c)
{
    if(n == 1)
    {
        cout << a<<"->"<<c<<endl;
        return 0;
    }
    else if(n > 1)
    {
        Hanoi(n - 1,a,c,b);
        Hanoi(1,a,b,c);
        Hanoi(n - 1,b,a,c);
    }
    else
    {
        cout << "error"<< endl;
        return -1;
    }
       
}

int main()
{
    int plate = 4;
    Hanoi(plate,'1','2','3');
    return 0;
}
