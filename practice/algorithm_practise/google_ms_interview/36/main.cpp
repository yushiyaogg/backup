#include <iostream>
#include <string.h>
using namespace std;

int Delete_chars(char* OriginalString, char* DeleteCharacter)
{
    int hash[256] = {0};
    char *scanptr = NULL;
    char *modifyptr = NULL;
    if(OriginalString == NULL||DeleteCharacter == NULL)
        return -1;
    for(int i = 0; i < sizeof(DeleteCharacter) -1; i ++)
    {
        hash[*(DeleteCharacter + i)] = 1;
    }

    scanptr = modifyptr = OriginalString;
    while(*scanptr != '\0')
    {
        if(hash[*(scanptr)] == 0)
        {
            memcpy(modifyptr,scanptr,1);//should use memcpy
            scanptr ++;
            modifyptr ++;
        }
        else
        {
            //*(modifyptr) = *(scanptr+1); char* can not use "="
            scanptr ++;
        }
    }
    memcpy(modifyptr,scanptr,1);
    return 0;

}

int main()
{
    char string1[] = "we are the champion. u are the loser.";
    char D_char[] = "aeiou";
    Delete_chars(string1,D_char);
    cout << string1<<endl;
}
