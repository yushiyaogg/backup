#include <iostream>
using namespace std;

class Clock
{
    private:
    public:
        int H,M,S;
        
      /*  Clock(int h , int m , int s )
        {
            H = h;
            M = m;
            S = s;
        }*/
/*	Clock()
	{
		H = M = S = 0;
	}*/

        int SetTime(int h, int m, int s)
        {
            H = (h >= 0&&h <= 24)? h : 0;
            M = (m >= 0&&m <= 60)? m : 0;
            S = (s >= 0&&s <= 60)? s : 0;
            return 0;
        }

        void ShowTime()
        {
            cout << H << ":" << M << ":" << S << endl;
        }

        ~Clock()
        {
            cout << "destructor"<< endl;
        }

};
class A:public Clock
{
public:
	int a1;
	int a2;
//	Clock C1;
};
int main()
{
    //Clock *Myclock = new Clock(1,1,1);
    //Myclock -> ShowTime();
    //Myclock -> SetTime(8,30,45);
    //Myclock -> ShowTime();
    A a;
    cout << "a.a1:"<<a.a1<<endl;
    cout << "a.a2:"<<a.a2<<endl;
  //  cout << "a.C1"<<a.C1.H<<endl;
}
