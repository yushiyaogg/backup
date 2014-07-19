#include <iostream>
#include <string.h>
using namespace std;
class MyString
{
    public:
        char *p_data;
        MyString(char* str)
        {
            p_data = NULL;
            if(str != NULL)
            {
                p_data = new char[strlen(str) + 1];
                strcpy(p_data,str);
            }
        }
        void operator= (const MyString &str)
        {
            if(&str == this)
            {
              //  return *this;
            }
            delete []p_data;
            p_data= NULL;
            p_data = new char[strlen(str.p_data) + 1];
            strcpy(p_data,str.p_data);
           // return *this;
        }
};

int operator+(MyString s1, MyString s2)
{
    return 0;
}

int main()
{
    char str[] = "abc";
    MyString mystring(str);
    MyString mystring1(NULL);
    MyString mystring2(NULL);
   // mystring2 = mystring1 = mystring;
    mystring1 = mystring;

//    cout << "mystring = "<< mystring.p_data<<endl;
  //  cout << "mystring1 = "<< mystring1.p_data<<endl;
  //  cout << "mystring2 = "<< mystring2.p_data<<endl;
   // int a;
   // a.operator+(1,2);
  // a.operator=(1);
   // cout << a <<endl;
   int a = mystring +mystring1;
   
   cout << a<<endl;
}
