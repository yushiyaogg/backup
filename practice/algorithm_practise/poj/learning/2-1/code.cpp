/*
 * =====================================================================================
 *
 *       Filename:  2_1.cpp
 *
 *    Description:  ji tu tong long
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
using namespace std;
#define RABIT_LEGS 4
#define CHIKEN_LEGS 2
int caculate(int legs)
{
    if(legs % 2 == 1){
        cout << 0 << " "<< 0 <<endl;
        return 0;
    }
    else{
        if(legs % 4 == 0){
            cout << legs/RABIT_LEGS << " "<< legs/CHIKEN_LEGS<<endl;
            return 0;
        }
        else{
            cout << legs/RABIT_LEGS + 1 << " "<<legs / CHIKEN_LEGS<<endl;
            return 0;
        }
    }
}
int main()
{
    int data_scale;
    int legs;
    int i = 0;
    cin >> data_scale;
    int *p = new int[data_scale];
    while(i < data_scale)
    {
        cin >> *(p + i);
        i ++;
    }
    i = 0;
    while(i < data_scale){
        caculate(*(p + i));
        i ++;
    }
    delete []p;

}

