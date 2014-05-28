#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int array[] = {1,2,3,4,5,6,7,8,9,0};
    vector<int> first_v;
    vector<int> second_v(array,array+sizeof(array)/sizeof(int));

    vector<int>::iterator it;

    it = second_v.begin();
    for(int i = 10;i < 30; i ++)
        second_v.push_back(i);
    cout << "==============before erase========"<<endl;
//    second_v.erase(it);
    cout << "===============after erase========"<<endl;
}
