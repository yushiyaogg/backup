#include <iostream>
using namespace std;

class X{
public:
	int x1;
	int x3;
	long x2;
	int x4;
//	int x3;
//	int virtual show();
};
class Y:public X{
//	int y1;
public:
	int y2;
};
/*
class Z:public virtual X{
	int z1;
};
class A : public Y, public Z{};
*/
int main()
{
	X x;
	Y y;
//	Z z;
//	A a;
	cout << "x :"<<sizeof(X)<<endl;
	cout << "y :"<<sizeof(Y)<<endl;

//	cout << "z :"<<sizeof(z)<<endl;
//	cout << "a :"<<sizeof(a)<<endl;
}
