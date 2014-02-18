#include <iostream>
using namespace std;

int LCS(char* string1, char* string2, int length1, int length2)
{
    int *matrix = new int[(length1 + 1)*(length2 + 1)];
    if(string1 == NULL||string2 == NULL||length1 == 0||length2 == 0)
    {
        return 0;
    }
    for(int i = 0; i <= length1; i ++)
    {
        for(int j = 0; j <= length2; j ++)
        {
            if(i == 0 ||j == 0)
                *(matrix + (i * (length2+1) + j)) = 0;
            else
            {
                if(*(string1 + i - 1) == *(string2 + j -1))
                {
                    *(matrix + (i * (length2 + 1) + j )) = 1 + *(matrix +((i -1) * (length2+1) + j -1));
                }
                else
                    *(matrix + (i * (length2+1) + j )) = *(matrix + ((i -1)* (length2+1)) + j) > *(matrix+(i * (length2+1) + j) -1)?*(matrix + ((i -1)* (length2+1)) + j):*(matrix+(i * (length2+1) + j) -1);
            }
        }
    }
    return *(matrix + ((length1 + 1) * length2 + length1 ) );
}

int main()
{
    char string1[] = "BDCABA";
    char string2[] = "ABCBDAB";
    char *ptr1 = string1;
    char *ptr2 = string2;
    int length1 = sizeof(string1) - 1;
    int length2 = sizeof(string2) - 1;
    cout << LCS(ptr1,ptr2,length1,length2)<<endl;
}
