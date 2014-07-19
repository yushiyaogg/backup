#include <set>
#include <iostream>
using namespace std;

int main()
{
    int i ;
    int ia[5] ={0,1,2,3,4};
    set<int> iset(ia,ia+5);

    cout << "size = "<< iset.size()<< endl;
    cout << "3 count=" << iset.count(3) << endl;
    
    iset.insert(3);
    cout << "size = " << iset.size() << endl;
    cout << "3 count=" << iset.count(3) << endl;
    
    iset.erase(3);
    cout << "size ="<< iset.size() << endl;
    cout << "3 count=" << iset.count(3) << endl;
    cout << "1 count" << iset.count(1) << endl;
}
