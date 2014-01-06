/*
 * =====================================================================================
 *
 *       Filename:  code.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/24/13 20:05:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (), 
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#include <iostream>
using namespace std;

int main()
{
    int road_length;
    int subway_number;
    int i,j;
    int subway_start;
    int subway_end;
    int number_tree = 0;
    scanf("%d%d",&road_length, &subway_number);

    bool trees[road_length + 1];
   // bool p = trees;
    for(i = 0; i < road_length + 1;i ++)
    {
       trees[i] = true;
    }
    for(i = 0 ; i < subway_number; i ++)
    {
        scanf("%d%d",&subway_start,&subway_end);
        for(j = subway_start;j < subway_end + 1 ; j ++)
        {
            trees[j] = false;
        }
    }
    for(i = 0; i < road_length + 1;i ++)
    {
        if(trees[i] ==  true)
            number_tree ++;
    }
    cout << number_tree<<endl;
    
   
}
