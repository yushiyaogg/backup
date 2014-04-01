#include <iostream>
using namespace std;
class Clock{
    private:
        int H,M,S;
    public:
        Clock(int h=0,int m=0,int s=0)
        {
            H=h,M=m,S=s;
            cout << "constructor:"<<H<< ":"<<M<<":"<<S<<endl;
        }
        ~Clock()
        {
            cout << "destructor:"<<H<<":"<<M<<":"<<S<<endl;
        }
        Clock(Clock &p)
        {
            cout << "copy constructor, vefore call:"<<H<<":"<<M<<":"<<S<<endl;
            H = p.H;
            M = p.M;
            S = p.S;
        }
};
Clock fun(Clock C)
{
    return C;
}

int main()
{
    Clock C1(8,0,0);
    Clock C2(9,0,0);
    Clock C3(C1);
    fun(C2);
    Clock C4;
    C4 = C2;
}


