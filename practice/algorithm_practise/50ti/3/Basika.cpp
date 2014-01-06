/*
 * =====================================================================================
 *
 *       Filename:  Basika.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/06/12 17:31:04
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

int factorial(int n)
{
    if(n == 0)
        return 1;
    else
        return n*factorial(n -1);
}
int Basika(int n)
{
    for(int i = 0 ; i < n ; i++)
    {
        for(int j = 0 ; j< n -i;j ++)
            cout<<" ";
        for(int j = 0; j < i + 1; j ++)
        {
            if(j == 0)
            {
                cout << "1";
                cout << " ";
            }
            else
            {
                cout <<factorial(i)/factorial(i -j)/factorial(j);
                   
                cout <<" ";
            }
        }
        cout <<endl;
    }
}

int main()
{
    Basika(12);
}
