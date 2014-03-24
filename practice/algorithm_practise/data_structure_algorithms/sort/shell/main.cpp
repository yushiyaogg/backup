#include <iostream>
using namespace std;
void ShellSort(int array[],int length)

{
    
    int d = length/2;   //设置希尔排序的增量
    int i ;
    int j;
    int temp;
    while(d>=1)    
    {
        for(i=d;i<length;i++)    
        {    
            temp=array[i];
            j=i-d;
            while(j>=0 && array[j]>temp)    
            {    
                array[j+d]=array[j];    
                j=j-d;    
            }    
            array[j+d] = temp;    
        }
        //Display(array,10);    
     d= d/2;    //缩小增量    
    }    
}

int main()
{
    int array[10] ={34,4565,234,345,67,24,4,6,7234,54};
    ShellSort(array,10);
    return 0;
}
