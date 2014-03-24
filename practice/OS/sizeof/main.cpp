#include <iostream>
using namespace std;
int main()
{
    char string[] = "1234567890";
    cout << "int:  "<<sizeof(int)<<endl;
    cout << "long: "<<sizeof(long)<<endl;
    cout << "char* :"<<sizeof(char*)<<endl;
    cout << "void* :"<<sizeof(void*)<<endl;
    cout << "char string[] = '1234567890':  "<<sizeof(string)<<endl;
}
