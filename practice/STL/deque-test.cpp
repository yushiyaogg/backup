#include <deque>
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    deque<int ,alloc,8> ideq(20,9);
    cout << "size=" <<ideq.size()<<endl;
}
