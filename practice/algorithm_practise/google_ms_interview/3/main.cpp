/////////////////////////////////////////////
//find the greatest sum of sub-arrays
//input :a array of int
//output: the greatest sum
////////////////////////////////////////////

#include <iostream>
using namespace std;

int great_sum_of_subarrays(int* p , int num)
{
    int sum = 0 ;
    int max = 0;
    int *head;
    int *rear;
    int i; 
    head = rear = p;
    for(i = 0; i < num; i ++)
    {
        if(*(p + i) > 0)
        {
            sum = sum + *(p + i);
            if(sum > max )
                max = sum;
        }
        else
        {
            if(sum + *(p + i) < 0)
            
                sum = 0;
            
            else
                sum = sum + *(p + i);
        }
    }
    return max;
}
int main()
{
    int * ptr;
    int num[] = {1,-2,3,10,-4,7,2,-5};
    ptr = num;
    int number = sizeof(num)/sizeof(int);
   // cout << number;
   int sum = great_sum_of_subarrays(ptr,number);
   cout << sum;

}
