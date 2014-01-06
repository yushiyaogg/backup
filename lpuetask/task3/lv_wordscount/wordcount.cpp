/*
 * =====================================================================================
 *
 *       Filename:  wordcount.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/14/12 04:38:58
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (), 
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#include <iostream>
#include <fcntl.h>
#include <string.h>
#include <map>
#include <string>
using namespace std;
int main(int argc, char* argv[])
{
    map<string,int> wordsmap;
    map<string,int>::iterator m_iter;
    int fd;
    int ret;
    char buff[4096];
    char buff_temp[4096];
    char buff_rest[100];
    int  rest = 0;
    char *head;
    char *rear;
    char *point; 
    int  num;
    if((fd = open("test", O_RDONLY)) < 0)
    {
        cout << "open error"<<endl;
        return -1;
    }
    while(1)
    {
        if((ret = read(fd, buff_temp,4000)) < 0)
        {
            cout << "read error"<< endl;
            return -1;
        }
        if(ret == 0)
        {
            return 0;
        }
        else
        {
            if(rest > 0)
            {
                memcpy(buff,buff_rest,rest);
                memcpy(buff+rest, buff_temp,ret);
                num = ret+ rest;
            }
            memcpy(buff,buff_temp,ret);
            num = ret;
            head = buff;
            rear = head + num;
            while(1)
            {
                if(head)
            }
        
        }
    }
}
