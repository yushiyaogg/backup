#include <iostream>
using namespace std;

class Parent
{
    public:
    int number;
    int set_num(int a)
    {
        cout << "this is parent" <<endl;
        number = a;
        return 0;
    }
    int show_num()
    {
        cout << "this is parent" <<endl;
        cout << "num =" << number << endl;
        return 0;
    }
    virtual int say_hello()
    {
        cout << "hello in parent"<<endl;
        return 0;
    }
};

class Child : public Parent
{
    public:
 //   int number;
    int set_num(int a)
    {
        cout << "this is child" <<endl;
        number = a;
        return 0;
    }
  /*  int show_num()
    {
        cout << "this is child" << endl;
        cout << "num =" << number << endl;
        return 0;
    }*/
    int say_hello()
    {
        cout << "hello in child" <<endl;
        return 0;
    }
};

int main()
{
    Parent parent;
   // parent.set_num(1);
  //  parent.show_num();
    parent.say_hello();
    Parent *parent_ptr = new Child;
    parent_ptr->say_hello();
 //   parent_ptr -> set_num(2);
 //   parent_ptr -> show_num();
    Child *child_ptr = (Child*)new Parent;
    child_ptr->say_hello();
  //  child_ptr -> set_num(3);
 //   child_ptr -> show_num();
    Child *child_ptr1 = new Child;
 //   child_ptr1 -> set_num(4);
  //  child_ptr1 -> show_num();
    child_ptr1->say_hello();
//addingsome
}
