#include <iostream>
using namespace std;

int swap(int *p1, int *p2)
{
    int temp = *p1;
    *p1 = *p2;
    *p2 = temp;
    return 0;
}
int QuickSorting(int *p , int len)
{
    int *first = NULL;
    int *last = NULL;
    int *mid = NULL;
    if(len == 0 || len == 1)
        return 0;
    first = p + 1;
    last = p + len -1;
    mid = p;
    while(first <= last)
    {
        if(*mid > *first)
        {
            swap(mid, first);
            mid ++;
            first ++;
        }
        else
        {
            swap(first,last);
            last --;
        }
    }
    QuickSorting(p ,mid -p);
    QuickSorting(mid + 1, len - (mid - p) - 1);
}

int main()
{
    int array[11] = {3,2,23423,565,223,456,768664,345,222,6,88656};
    QuickSorting(array,sizeof(array)/sizeof(int));
    for(int i = 0; i < sizeof(array)/sizeof(int); i ++ )
    {
        cout << array[i]<<endl;
    }
    return 0;
}
