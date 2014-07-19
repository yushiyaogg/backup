#include <iostream>
using namespace std;
const int a = 11;
int main()
{
    const int b =22;
    int *ptr;
   // int address_a = (int) &b;
    ptr = (int*) &b;
    *ptr = 21;
}
