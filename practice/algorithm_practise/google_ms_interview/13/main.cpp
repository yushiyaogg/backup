#include <iostream>
using namespace std;


int FirstNotRepeatChar(char* p, int num)
{
    int hashtable[256] = {0};
    if(p == NULL)
    {   
        return -1;
    }
    for(int i = 0; i < num; i ++)
    {
        hashtable[*(p + i)] ++;
        
    }
    for(int i = 0 ; i < num; i ++)
    {
        if(hashtable[*(p + i)] == 1)
        {
            return i;
        }
    }
    return -1;
    
}

int main()
{
    char var[] = "asdjkf 2  3r90q38471``wuoqpe as ASAOPS$%^&*(09&%rihisdrhyiq30YUITGKU(*)&^*(%^";
    char *ptr = var;
    int offset = FirstNotRepeatChar(ptr,sizeof(var)-1);
    if(offset != -1)
        cout <<var[offset]<<endl;
    return 0;
}
