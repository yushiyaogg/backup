#include <iostream>
using namespace std;

int main()
{
    char original_string[10000];
    int hash_table[36];
    char *ptr = NULL;
    int error = 0;
    int flag = 0;
    int *hashptr = hash_table;
    ptr = original_string;
    while(cin >> original_string)
    {
        while(*ptr != '\0')
        {
            if((*ptr >= '0'&& *ptr <= '9') || (*ptr >= 'a'&&*ptr <= 'z') )
            {
                if(*ptr >= '0' && *ptr <= '9')
                {
                    hash_table[*ptr - '0'] ++;
                    ptr ++;
                    continue;
                }
                else 
                {
                    hash_table[*ptr - 'a' + 10] ++;
                    ptr ++ ;
                    continue;
                }
            }
            else
            {
                error = 1;
                break;
            }
        }

        if(error == 1)
        {
            cout << "<invalid input string>"<<endl;
            error = 0;
            ptr = original_string;
            for(int i= 0 ; i < 36; i++)
            {
                hash_table[i] = 0;
            }
        }
        else
        {
            while(!flag)
            {
                flag = 1;
                for(int i = 0 ; i < 36; i ++ )
                {
                    if(hash_table[i] != 0)
                    {
                        flag = 0;
                        if(i >= 0 && i <= 9)
                        {
                            cout << (char)('0'+i);
                            hash_table[i]--;
                        }
                        else
                        {
                            cout << (char)('a'+i - 10);
                            hash_table[i]--;
                        }
                    }
                }
            }
            cout <<endl;
            ptr = original_string;
            flag = 0;

        }


    }
    return 0;
}
