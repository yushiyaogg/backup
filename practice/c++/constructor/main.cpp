#include <iostream>
using namespace std;

class Clock
{
    private:
        int H,M,S;
    public:
        
   /*     Clock()
        {
            H = 0;
            M = 0;
            S = 0;
        }*/
        Clock(int h , int m , int s )
        {
            H = h;
            M = m;
            S = s;
        }

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

int main()
{
    Clock *Myclock = new Clock();
    Myclock -> ShowTime();
    Myclock -> SetTime(8,30,45);
    Myclock -> ShowTime();
}
