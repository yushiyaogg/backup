/*
 * =====================================================================================
 *
 *       Filename:  2_2.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/20/13 20:34:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (), 
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#include <iostream>
#include <math.h>
#include <stdlib.h>
using namespace std;
int caculate(char number_start,char number_end,char character_start,char character_end)
{
    if(abs(number_start-number_end) > abs(character_start-character_end))
        cout << abs(number_start-number_end);
    else
        cout << abs(character_start-character_end);

    cout << " ";

    if(number_start == number_end && character_start == character_end)
        cout << 0;
    else if(number_start == number_end || character_start == character_end
            || (number_start - number_end) == (character_start - character_end))
        cout << 1;
    else 
        cout << 2;

    cout << " ";

    if(number_start == number_end && character_start == character_end)
        cout << 0;
    else if(number_start == number_end || character_start == character_end)
        cout << 1;
    else
        cout << 2;

    cout << " ";
    if( (abs(number_start - number_end + character_start - character_end)) % 2 == 1 )
        cout << "Inf"<<endl;
    else if(number_start == number_end && character_start == character_end)
        cout << 0<< endl;
    else if(abs(number_start - number_end) == abs(character_start - character_end))
        cout << 1 <<endl;
    else 
        cout << 2 <<endl;
}
int main()
{
    int data_scale;
    int i = 0;
    char number_start;
    char number_end;
    char character_start;
    char character_end;
    char blank;
    char begin[3];
    char end[3];
    cin >> data_scale;
    while(i < data_scale)
    {
        scanf("%s %s",begin,end);
        character_start = begin[0];
        number_start = begin[1];
        character_end = end[0];
        number_end =  end[1];
        caculate(number_start,number_end,character_start,character_end);
        i ++;
    }

}

