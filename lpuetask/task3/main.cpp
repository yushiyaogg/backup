/*
 * =====================================================================================
 *
 *       Filename:  
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/15/12 09:26:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   ) 
 *        Company:  NDSL UESTC
 *
 * =====================================================================================
 */


#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "WordsCount.h"
#include "WordsCount.cpp"
#define BUFSIZE 4096
#define WRITETHREADNUM 10

int fdSource,fdDest;//源文件、目的文件描述符
int fd[2];//管道文件描述符
struct dataDelieve
{
    int frequency;
    char ptr[60];
};


int wordcount(char* dirpath)
{
    DIR *dp;
    struct dirent * dirp;
    class WordsCount wc;
    pid_t pid;
    int len;
    int ret;
    int stat;
    struct stat stat_buf;
    char path[500];
    char temp_path[500];
    memset(path,0,500);
    memset(temp_path,0,500);
    strcat(path,dirpath);
    struct dataDelieve send_data;
    if((dp = opendir(dirpath))== NULL)
    {
        cout << "opendir error "<<endl;
        return -1;
    }
        strcat(path,"/");
    while((dirp = readdir(dp)) != NULL)
    {
        memset(temp_path,0,500);
        strcat(temp_path,path);
        strcat(temp_path,dirp->d_name);
        if(strcmp(dirp->d_name, ".") ==0 || strcmp(dirp->d_name, "..") == 0)
            continue;
        if(dirp->d_type == DT_DIR)
        {
            if((pid = fork()) < 0) 
            {
                cout << "fork error"<<endl;
                return -1;
            }
            else if (pid == 0)
            {
                wordcount(temp_path);
                return 0;
            }
            else
            {
                continue;    
            }
        }
        else
        {
            if((fdSource = open(temp_path,O_RDONLY)) < 0)
            {
                cout << "open file error"<<endl;
                return -1;
            }
            if(lstat(temp_path,&stat_buf) < 0)
            {
                cout <<"lstat error"<<endl;
                return -1;
            }
            len = stat_buf.st_size;
            wc.input(temp_path,0,len);
            wc.count();
           /*  while(wc.getOneItem() == "ok");
            wc.m_bIsFirstToGetItem = true;*/
        }
    }
    memset(&send_data,0,64);
    char *dataptr;
    int  *frequencyptr;
    while(wc.getOneItem(dataptr,frequencyptr) == 1)
    {
        memcpy(send_data.ptr,dataptr,60);
        memcpy(&(send_data.frequency),frequencyptr,4);
        while((ret = write(fd[1],&send_data,64)) == 0)
            ;
        if(ret != 64)
        {
            cout <<"write pipe error"<<endl;
            cout << "write ret = "<<ret<<endl;
            cout << strerror(errno)<<endl;
            return -1;
        }
    }
    while(wait(&stat) == -1)
    {
        close(fd[1]);
        return 0;
    }

}
int main(int argc, char *argv[])
{
    pid_t pid;
    int ret;
    int stat;
    struct dataDelieve recieve_data;
    map <string,int> total_wordsmap;
    map <string, int>::iterator map_iter;
    string words;
    if(argc != 3)
    {
        cout << "usage: wordscan scan_dir result_file"<<endl;
        return -1;
    }
    if(pipe(fd) < 0)
    {
        cout << "pipe error "<<endl;
        return -1;
    }
    char a[] ="./temp_sov";
    if((pid = fork()) < 0)
    {
        cout << "fork error"<<endl;
        return -1;
    }
    else if(pid == 0)
    {
        close (fd[0]);
        wordcount(argv[1]);
        exit (0);
    }
    else
    {
        close (fd[1]);
        while((ret = read(fd[0],&recieve_data,64)) == 64)
        {
            words = recieve_data.ptr;
            if((map_iter = total_wordsmap.find(words)) != total_wordsmap.end())
            {
                map_iter->second = map_iter->second + recieve_data.frequency;
                continue;
            }
            else
            {
               total_wordsmap[recieve_data.ptr] = recieve_data.frequency; 
            }
        }
        if(ret == 0)
        {
            close(fd[0]);
        }
        else
        {
            cout <<"read pipe error"<<endl;
            cout << "ret ="<<ret<<endl;
            return -1;
        }
    }

    while(pid = wait(&stat) != -1)
    {
        cout << "chilren return"<<endl;
    }
 /*     if((fdDest = open("result",O_RDWR|O_TRUNC)) < 0)
    {
        cout <<"open result error"<<endl;
        return -1;
    }*/
    map_iter = total_wordsmap.begin();
    
    ofstream file(argv[2],ios::out);
    while(map_iter != total_wordsmap.end())
    {
        file << map_iter->first;
        file << "\t\t\t\t\t\t\t";
        file << map_iter->second;
        file << "\n";
        map_iter ++;
       /* char *inputcontent;
        char *inputfrequency;
        inputcontent = const_cast <char*>((map_iter->first).c_str());
        inputfrequency =itoa( map_iter->second);
        write(fdDest,inputcontent,strlen(inputcontent));
        write(fdDest,"/t/t/t/t/t/t",6);
        write*/

    }
    file.close();
    cout <<"end of the count"<<endl;

}
