#include "header.h"

int main()
{
    char*t;
    int i;
    t=new char[8];
    cout<<"t length:"<<strlen(t)<<endl;
    memset(t,'\0',8);
    cout<<"t length:"<<strlen(t)<<endl;
    delete t;
    return 0;
}
