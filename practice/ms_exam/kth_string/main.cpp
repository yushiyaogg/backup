#include <iostream>
using namespace std;

int swap(char* p1, char* p2)
{
    char temp = *p1;
    *p1 = *p2;
    *p2 = temp;
    return 0;
}

int main()
{
     int size;
    int number_zero;
    int number_one;
    int k;
    cin >> size;
    for(int i = 0; i < size ; i ++)
    {
        cin >> number_zero >> number_one >> k;
        char* string = new char[number_zero + number_one];
        char* ptr = string;
        for(int i = 0; i < number_zero; i ++)
            *ptr = '0';
        for(int i = 0; i < number_one; i ++)
            *ptr = '1';
        while(--k)
        {
            char *find_zero = ptr+ number_zero + number_one;
            if(*find_zero !='0')
                find_zero --;
            if(*(fine_zero+1) == '1')
            {
                swap(find_zero, find_zero + 1);
                continue;
            }
        }

    }
  /*  char a = 'a';
    char b = 'b';
    swap(&a,&b);
    cout << a <<b;*/
}
