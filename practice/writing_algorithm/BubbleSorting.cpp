#include <iostream>
using namespace std;

int swap(int *p1, int *p2)
{
    int temp;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
};

int BubbleSorting(int *p,int len)
{
    
    for(int i = 0; i < len; i ++)
    {
        for(int j = 0; j < len - i - 1; j ++)
        {
            if (*(p + j ) < *(p + j + 1))
                swap(p + j ,p + j + 1);
        }
    }
}

int main()
{
    int array[2] = {12312};
    BubbleSorting(array,1);
    cout << "end"<<endl;
}
