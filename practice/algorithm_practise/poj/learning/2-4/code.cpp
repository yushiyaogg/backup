/*
 * =====================================================================================
 *
 *       Filename:  code.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/26/13 19:43:35
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (), 
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#include <iostream>
#include <stdio.h>
using namespace std;

int main()
{
    int size_1 = 0; 
    int size_2 = 0;
    int size_3 = 0;
    int size_4 = 0;
    int size_5 = 0;
    int size_6 = 0;
    int number_box = 0;
    int rest_size_2 = 0;
    int rest_size_1 = 0;
    cin >> size_1 >>size_2 >> size_3 >> size_4 >> size_5 >> size_6;
    while(size_1 != 0 || size_2 != 0 || size_3 != 0 ||
            size_4 != 0 || size_5 != 0 || size_6 != 0)
    {
        number_box = size_6;
        if(size_5)
        {
            number_box = number_box + size_5;
            rest_size_1 = 11 * size_5;
        }
        if(size_4)
        {
            number_box = number_box + size_4;
            rest_size_2 = 5 * size_4;
        }
        if(size_3)
        {
            if (size_3 % 4 == 0)
                number_box = number_box + size_3 / 4;
            else if(size_3 % 4 == 1)
            {
                number_box = number_box + size_3 / 4 + 1;
                rest_size_2 = rest_size_2 + 5;
                rest_size_1 = rest_size_1 + 7;
            }
            else if(size_3 % 4 == 2)
            {
                number_box = number_box + size_3 / 4 + 1;
                rest_size_2 = rest_size_2 + 3;
                rest_size_1 = rest_size_1 + 6;
            }
            else if(size_3 % 4 == 3)
            {
                number_box = number_box + size_3 / 4 + 1;
                rest_size_2 = rest_size_2 + 1;
                rest_size_1 = rest_size_1 + 5;
            }
        }
        if(size_2)
        {
            if(size_2 < rest_size_2)
            {
                rest_size_1 = (rest_size_2 - size_2) * 4 + rest_size_1;
            }
            if(size_2 > rest_size_2)
            {
                int size_2_need_boxes = size_2 - rest_size_2;
                if(size_2_need_boxes % 9 != 0)
                {
                    number_box = size_2_need_boxes / 9 + 1 + number_box;
                    rest_size_1 = (9 - size_2_need_boxes % 9) * 4 + rest_size_1;
                }
                number_box = size_2_need_boxes / 9 + 1 + number_box;
            }
        }
        if(size_1)
        {
            if(size_1 > rest_size_1)
            {
                if((size_1 - rest_size_1) % 36 != 0)
                    number_box = number_box + (size_1 - rest_size_1) / 36 + 1;
                else
                    number_box = number_box + (size_1 - rest_size_1) / 36;
            }
        }
        cout << number_box << endl;
       // cout << size_1 << size_2 << size_3 << size_4 << size_5 << size_6;
        cin >> size_1 >> size_2 >> size_3 >> size_4 >> size_5 >> size_6;
    }
}
