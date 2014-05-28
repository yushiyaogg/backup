#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int array[] = {1,2,3,4,5,6,7,8,9,0};
    vector<int> first_v;
    vector<int> second_v(array,array+sizeof(array)/sizeof(int));
    vector<int> third_v(4, 99);
    vector<int> fourth_v(second_v);
    vector<int> fifth_v(second_v.begin(), second_v.end());

    vector<int>::iterator it;
    vector<int>::iterator it_begin;
    vector<int>::iterator it_end;
    third_v[1] = 100;
    third_v.push_back(123);
    cout << "third_v back:" << third_v.back()<<endl;
    third_v.clear();

    it_begin = second_v.begin();
    it_end = second_v.end();
    second_v.erase(it_begin,it_end);


    cout << "===============first_v================"<<endl;
    for(int i= 0; i < first_v.size(); i ++)
    {
        cout << first_v[i]<<endl;
    }
    cout << "===============first_v================"<<endl;
    cout << "first_v.size ="<<first_v.size()<<endl;
    cout << "first_v.capacity = "<< first_v.capacity()<<endl;

    cout << "===============second_v================"<<endl;
    for(int i = 0; i < second_v.size(); i ++)
    {
        cout << second_v[i]<<endl;
    }
    cout << "===============second_v================"<<endl;
    cout << "second_v.size ="<<second_v.size()<<endl;
    cout << "second_v.capacity = "<< second_v.capacity()<<endl;
    
    cout << "===============third_v================"<<endl;
    for(int i = 0; i < third_v.size(); i ++)
    {
        cout << third_v[i]<<endl;
    }
    cout << "===============third_v================"<<endl;
    cout << "third_v.size ="<<third_v.size()<<endl;
    cout << "third_v.capacity = "<< third_v.capacity()<<endl;
    
    cout << "===============fourth_v================"<<endl;
    for(int i = 0; i < fourth_v.size();i ++)
    {
        cout << fourth_v[i]<<endl;
    }
    cout << "===============fourth_v================"<<endl;
    cout << "fourth_v.size ="<<fourth_v.size()<<endl;
    cout << "fourth_v.capacity = "<< fourth_v.capacity()<<endl;
    cout << "fourth_v.back" << fourth_v.back()<<endl;
    fourth_v.push_back(1000);
    cout << "fourth_v.back" << fourth_v.back()<<endl;

    
    cout << "===============fifth_v================"<<endl;
    for(int i = 0; i < fifth_v.size(); i ++)
    {
        cout << fifth_v[i]<<endl;
    }
    cout << "===============fifth_v================"<<endl;
    it = fifth_v.begin();
    fifth_v.erase(it);
    cout << "fifth_v.size ="<<fifth_v.size()<<endl;
    cout << "fifth_v.capacity = "<< fifth_v.capacity()<<endl;
    first_v.~vector();
}
