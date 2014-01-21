///////////////////////////////////////////
//
//caculte the result of 1+2+3+......+n 
//without * / and if while for etc;
//////////////////////////////////////////


#include <iostream>
using namespace std;

int addfunc(int i){
    int r = 0;
    i && (r= i + addfunc(i-1) );
    return r;
}

int main()
{
    int sum = addfunc(8);
    cout <<"sum is "<<sum<<endl; 
}
