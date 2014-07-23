#include <iostream>
using namespace std;
class Complex
{
public:
	double real;
	double image;
	void display()
	{
		cout << "real is"<<real<<"image is"<<image<<endl;
	}	
};
Complex operator+(Complex left, Complex right)
{
	Complex temp;
	temp.real = left.real + right.real;
	temp.image = left.image + right.image;
	return temp;
}

int main()
{
	Complex A;
	Complex B;
	Complex C;
	A.real = 1;
	A.image =1;
	B.real = 2;
	B.image =2;
	C = A + B;
	C.display();

}
