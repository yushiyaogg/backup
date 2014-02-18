#include<iostream>
using namespace std;

int NumberOf_1(int num)
{
    int flag = 1;
    int count = 0;
    while(flag != 0)
    {
        if(flag & num)
        {
            count ++;
            cout <<1;
        }
        cout <<0;
        flag = flag << 1;
    }
    return count;
}


int main()
{
    int a = 10;
    cout << endl<<NumberOf_1(a) <<endl;
}
