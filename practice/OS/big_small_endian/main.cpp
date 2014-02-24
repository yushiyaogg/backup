#include <iostream>
using namespace std;
union A
{
    int value;
    char character[4];
};

int main()
{
    A A1;
    A1.value = 0x12345678;
    if(A1.character[0] == 0x78)
        cout << "big"<<endl;
    else
        cout <<"small"<<endl;
    cout << A1.character[0]<<A1.character[1]<<A1.character[2]<<A1.character[3]<<endl;
    return 0;
}
