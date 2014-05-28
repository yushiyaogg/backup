#include <iostream>
using namespace std;

int BiSearch(int *p, int len , int key)
{
    int *first = p;
    int *last = p + len -1;
    int *mid = NULL;
    while(first <= last)
    {
        mid = first + (last - first) / 2;
        if(*( mid) == key)
        {
            cout << "get it"<<endl;
            return 0;
        }       
        else if(*(mid) < key)
        {
            first = mid + 1;
            continue;
        }
        else
        {
            last = mid - 1;
            continue;
        }

    }
    cout << "miss it"<<endl;
    return 0;
}

int main()
{
    int array[] = {1,2,3,4,5,6,7,8,9,11,12,143,45345};
    BiSearch(array, sizeof(array)/sizeof(int), 15);
}
