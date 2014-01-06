/*
 * =====================================================================================
 *
 *       Filename:  task.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/17/12 16:04:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (), 
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
using namespace std;
int Input(int* &array,int &len);
int Combination_number(int ,int);
void Rcombination(int*, int ,int&,int);
int main()
{
    int* array = NULL;
    int array_length;
    int select_number;
    int total;

    if(Input(array,array_length) < 0)
        return -1;
    cout << "input sucess"<<endl;
    cout << "please input the size you want to select"<<endl;
    cin >> select_number;

    total = Combination_number(select_number + array_length -1,select_number);
    
    Rcombination(array,array_length,total,select_number);

    cout <<"total = "<<total<<endl;
}

int Input(int* &array,int &len)
{
    cout <<"please input the size of element"<<endl;
    cout << "size :";
    cin >> len;
    if(len <= 0)
    {
        cout << "the size is out of rule"<<endl;
        return -1;
    }
    else
    {
        array = new int(len);
    }
    cout << "please input the size of every element"<<endl;
    for(int i = 0; i < len; i ++)
    {
        cin >> *(array + i);
        if(*(array +i) < 0)
        {
            cout << "please input a number larger than 0"<<endl;
            i --;
            continue;
        }
        
    }
    return 0;
    
}
int Combination_number(int n1, int r1)
{
    if(r1> n1) return 0;
    else if(r1 == 0) return 1;
    else
    {
        int t = 0, result = 1,b = 0,i = 0,re = 1;

        b = n1-r1;
        if(b < n1/2){
            t = b;
            b = r1;
            r1 = t;
        }
        for(;n1>b;n1--)
        {
            result = result*n1;
        }
        for(i = 2; i <= r1; i++)
            re = re * i;
        result = result/re;
        return result;
    }
}

void Rcombination(int* array, int length, int &total,int select_number)
{
    int sign[length];
    int len =0;
    int quality = 0;
    int circle = pow(2,length) - 1;
    int number = 0;
    int p ;
    int j = 0;
    for(int i = 0; i < length; i++)
        sign[i] = 0;
    for(int i = 0;i <= circle; i++)
    {
        j =0;
        for(int k = 0;k < length;k ++)
            if(sign[k])
            {
                number = number +*(array + k);
                len = len + 1;
            }
        if(number > 0)
        {
            int t = 0;
            if(len%2 == 0)
                p = 1;
            else
                p = -1;
            if(select_number - number > len)
            {
                quality = Combination_number(length + select_number- number -len-1,select_number -number-len);
                total = total + p * quality;
            }
            else if(select_number - number == len)
                total =total + p;
        }
        number = 0;
        len =0;
        
        while(1)
        {
            if(sign[j] == 0)
            {
                sign[j] = 1;
                break;
            }
            else if(sign[j] == 1)
            {
                sign[j] = 0;
                j ++;
            }
                if(j == length)
                    break;

        }
    }
}
