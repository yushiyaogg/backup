#include <iostream>
using namespace std;

class A
{
public:
	int a;
	virtual int fun()=0;
/*	{
		cout << "A virtual"<<endl;
		return 1;
	}*/
};

class B: public A
{
	int fun()
	{
		cout << "B virtual"<<endl;
		return 1;
	}
};
int main()
{
	class A* ptr;
//	class A a;
//	a.fun();
	ptr = new B;
	ptr -> fun();
	return 0;
}
