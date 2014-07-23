#include <iostream>
using namespace std;

int main()
{
	int i = 0;
	int m = 1;
	int &p = i;
	p = m;
	cout << "p:" << p<<endl;
}
