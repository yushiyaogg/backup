/*
 * =====================================================================================
 *
 *       Filename:  eight_queen.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/16/12 17:58:18
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#include <iostream>
using namespace std;
#define N 8
    int square[N][N]= {0};
    int total = 0;
/*int eight_queen()
{
    int square[N][N]= {0};
    int line_i = 0;
    int row_i = 0;
    int row_j = 0;
    int line[N]= {-1};
    int row[N] = {-1,-1,-1,-1,-1,-1,-1,-1};
    for(line_i = 0; line_i < N; line_i ++)
    {
        line[line_i] = line_i;
    }
    for(line_i = 0 ;line_i < N; line_i ++)
    {
        int fill_in_row = 0;
        row_j = 0;
            while(row[row_j] != -1)
            {
                if(fill_in_row == row[row_j]||fill_in_row - row[row_j]==line_i - line[row_j])
                {
                    fill_in_row ++;
                    row_j = 0;
                    continue;
                }
                else
                    row_j ++;
            }
            row[line_i]= fill_in_row;

     }
     for(int i = 0; i< N ;i ++)
     {
        square[line[i]][row[i]]=1;
     }
     for(int i=0 ; i < N ;i ++)
     {
         for(int j=0 ; j < N ; j ++)
         {
            cout << square[i][j];
            cout << "  ";  
         }
         cout<<endl;
     }

    
}*/
int eight_queen(int* &line,int* &row)
{
    int index=1;
    while(1)
    {
        if(index == 9)
            break;
        if(line[index-1] != -1)
            index++;
        else
            break;
    }
    if(index == 9)
    {
        total ++;
        for(int i = 0; i < N; i ++)
        {
           square[line[i]][row[i]] = 1;
        }
        for(int i = 0; i < N; i ++)
        {
            for(int j = 0 ; j< N ; j ++)
            {
                cout << square[i][j];
                cout << "  ";
            }
            cout <<endl;
        }
        cout <<endl <<endl;
        for(int i = 0;i < N; i++)
        {
            for(int j = 0 ; j < N; j++)
            {
                square[i][j]= 0;
            }
        }
                                /*   for(int i = 0; i <N ; i ++)
                                       cout << line[i]<<" ";
                                   cout <<endl;
                                   for(int i = 0; i < N ;i ++)
                                       cout <<row[i]<<" ";
                                   cout <<endl<<endl;*/
        return 1;
    }
    else
    {
        int probe_line=0;
        int probe_row=0;
        for(int i = 0; i < N; i ++)
        {
            int available_mark = 1;
            for(int i = 0 ;i <index; i ++)
            {
                if(probe_line == line[i])
                {
                    available_mark = 0;
                    break;
                }
            }
            if(available_mark==1)
            {
                   for(int j = 0; j < N ; j ++)
                   {
                       int available_mark = 1;
                       for(int j = 0 ;j <index; j++)
                       {
                           if(probe_row == row[j])
                           {
                               available_mark = 0;
                               break;
                           }
                       }
                       if(available_mark ==1)
                       {
                               int available_mark = 1;
                               for(int k = 0;k < index;k++)
                               {
                                   if(probe_line-line[k]==probe_row-row[k]||probe_line-line[k]==row[k]-probe_row)
                                   {
                                       available_mark = 0;
                                       break;
                                   }
                                    
                               }
                               if(available_mark == 1)
                               {
                                  line[index-1] = probe_line;
                                   row[index-1] = probe_row;
                                 /*  for(int i = 0; i <N ; i ++)
                                       cout << line[i]<<" ";
                                   cout <<endl;
                                   for(int i = 0; i < N ;i ++)
                                       cout <<row[i]<<" ";
                                   cout <<endl<<endl;*/
                                   eight_queen(line,row);
                               }
                           
                       }
                       probe_row++;
                   }
                

            line[index -1] = -1;
            row[index-1] =-11;
            return 1;
            }
            probe_row = 0;
            probe_line++;

        }
    }
}

int main(int argc,char * argv[])
{
    int line_locate[N]= {-1,-1,-1,-1,-1,-1,-1,-1};
    int row_locate[N] = {-11,-11,-11,-11,-11,-11,-11,-11};
    int* line = line_locate;
    int* row = row_locate;
    eight_queen(line,row);
    cout <<total<<endl;
}
