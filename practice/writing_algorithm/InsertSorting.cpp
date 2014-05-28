#include <iostream>
using namespace std;
int swap(int *p1, int *p2)
{
    int temp;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
    return 0;
}

int InsertSorting(int *p,int len)
{
    int temp;
    int j;
    for(int i = 1; i < len; i ++)
    {
        for(j = 0; *(p + j) < *(p + i); j ++)
        {}
        for(int m = i; m > j; m --)
        {
            swap(p+m,p+m-1);
        }
    }
}

int main()
{
    int array[1] = {4};
    InsertSorting(array,1);
    cout << "end"<<endl;
}
