#include <iostream>
using namespace std;
int k = 300;
const int i = 100;
#define n 10
const int j = 200;
int fun (int i = 1, int j =2)
{
    const int k = 3;
    static int l =0;
    char *p = new char[n+1];
    for(int m = 0; m < n ; m ++)
        *(p + m) = 'A'+ m;
    p[m] = '\0';
    cout << "Address of parameter variable:"<<endl;
    cout << "&i = " << &i << "\t" << "&j = " << &j <<endl;
    cout << "Address of local variable:" << endl;
    cout << "&k = " << &k << "\t" << "&p = " << &p << "\t" << "&m = "<< &m <<endl;
    cout << "Address of static local variable:" << endl;
    cout << "&l = "<< &l << endl;
    cout << "Address of heap: " << (void *)p << endl;
    cout << "before delete p =" << p << endl;
    delete []p;
    cout << "after delete: "<< (void *)p <<endl;
    cout << "p =" << p << endl;
    return 0;
}

int main()
{
    fun();
    cout << "Address of global variable: " << endl;
    cout << "&i = " << &i << "\t" << "&j = " << &j << "\t" << "&k = " << &k << endl;
    cout << "Address of function: " << endl;
    cout << "&fun = " << &fun << "\t" << "&main =" << &main << endl;
    return 0;
}



