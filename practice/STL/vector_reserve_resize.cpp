#include <vector>
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    vector<int> vect;       
    vect.resize(100);    //分配100个空间
    vect.push_back(1);
    vect.push_back(2);
    vect.push_back(3);
    vect.push_back(4);
    cout<<"vect.size"<<vect.size()<<endl; //现在size和capacity都是104
    cout << "vect.capacity" << vect.capacity()<<endl;
    int i = 0;
    for (i = 0; i < 104; i++)
    {
      //  cout<<vect[i]<<endl; 
    }
    vector<int> vect2;       
    vect2.reserve(100);    
    vect2.push_back(1);
    vect2.push_back(2);
    vect2.push_back(3);
    vect2.push_back(4);
    cout<<"vect2.size ="<<vect2.size()<<endl; 
    cout << "vect2.capacity" <<vect2.capacity()<<endl;
    int j = 0;
    for (j = 0; j < 104; j++)
    {
       // cout<<vect2[j]<<endl; 
    }
    return 0;
}
