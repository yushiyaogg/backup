#include <iomanip>
#include <sstream>
#include <iostream>
#include <time.h>
#include <cmath>
#include <string>
#include <sys/signal.h>
using namespace std;
int main()
{
    string o_string = "1";
    int num ;
    stringstream temp;
    temp << o_string;
    temp >> num;
    cout <<num <<endl;
}
