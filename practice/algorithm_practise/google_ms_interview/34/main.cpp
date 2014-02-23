#include <iostream>
using namespace std;

int Find2Different(int *ptr, unsigned int length,int &first_number,int &second_number)
{
    int flag = 0;
    int mark = 1;
    first_number = 0;
    second_number = 0;
    for(int i = 0;i < length; i ++)
        flag = flag ^ *(ptr + i);
    if(flag == 0)
        return -1;
    for(;;)
    {
        if(flag % 2 == 1)
            break;
        else
        {
            mark = mark << 1;
            flag = flag >> 1;
        }
    }
    for(int i = 0; i < length; i ++)
    {
        if(mark & *(ptr + i))
            first_number = first_number ^ *(ptr + i);
        else
            second_number = second_number ^ *(ptr + i);
    }
    return 0;


}

int main()
{
    int int_string[]= {1,1,2,2,3,3,4,4,1,6};
    int length = sizeof(int_string)/sizeof(int);
    int num1 = 0;
    int num2 = 0;
    if(Find2Different(int_string,length,num1,num2) == 0)
        {
            cout<<num1<<endl;
            cout<<num2<<endl;
        }
    else
        cout<<"error input"<<endl;
  //  cout <<0x1^ 0x1 <<endl;
  //  cout << 0x0^0x0 <<endl;
}
