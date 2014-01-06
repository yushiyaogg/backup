/*
 * =====================================================================================
 *
 *       Filename:  maze.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/12/12 14:30:46
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

int visit(int *_entry, int *_exit,int *maze, int len,int wid)
{
    int maze_entry[2];
    int maze_exit[2];
    int position[2];
    maze_entry[0] = *_entry;
    maze_entry[1] = *(_entry+ 1);
    maze_exit[0] = *_exit;
    maze_exit[1] = *(_exit + 1);
    position[0] = maze_entry[0];
    position[1] = maze_entry[1];
    while((position[0] != maze_exit[0])||(position[1] != maze_exit[1]))
    {
        *(maze + position[0] * wid + position[1] ) = 1;
        if(*(maze + position[0] * wid + position[1] + 1) == 0)
        {
            position[1] = position[1] + 1;
            continue;
        }
        else if(*(maze +( position[0] + 1) * wid + position[1] ) == 0)
        {
            position[0] = position[0] + 1;
            continue;
        }
        else if(*(maze + position[0] * wid + position[1] - 1) == 0)
        {
            position[1] = position[1] - 1;
            continue;
        }
        else if(*(maze + (position[0] - 1) * wid + position[1] ) == 0)
        {
            position[0] = position[0] - 1;
            continue;
        }
        else if(*(maze + position[0] * wid + position[1] + 1) == 1)
        {
            *(maze + position[0] * wid + position[1]) = 3;
            position[1] = position[1] + 1;
            continue;
        }
        else if(*(maze + position[0] * wid + position[1] - 1) == 1)
        {
            *(maze + position[0] * wid + position[1]) = 3;
            position[1] = position[1] - 1;
            continue;
        }
        else if(*(maze + (position[0] + 1) * wid + position[1] ) == 1)
        {
            *(maze + position[0] * wid + position[1]) = 3;
            position[0] = position[0] + 1;
            continue;
        }
        else if(*(maze + (position[0] - 1)* wid + position[1] ) == 1)
        {
            *(maze + position[0]  * wid + position[1]) = 3;
            position[0] = position[0] - 1;
            continue;
        }
        else
            return -1;

    }
    *(maze +position[0] * wid +position[1]) = 1;
    return 0;
}

int main()
{
    int len = 7;
    int wid = 7;
    int i,j;
    int entry[2]= {1,1};
    int exit[2]  = {5,5};
    int maze[7][7] = {
        {2,2,2,2,2,2,2},
        {2,0,0,0,0,0,2},
        {2,0,2,0,2,0,2},
        {2,0,0,2,0,0,2},
        {2,2,0,2,0,0,2},
        {2,0,0,0,0,0,2},
        {2,2,2,2,2,2,2},
    };
    int *maze_ptr = &maze[0][0];
    for(i = 0; i < len; i ++)
    {
        for(j = 0; j < wid; j ++)
        {
            cout <<maze[i][j]<<" ";
        }
        cout <<endl;
    }
    if(visit(entry,exit,maze_ptr,len,wid) < 0)
    {
        cout << "no path"<<endl;
        return -1;
    }
for(i = 0;i < 5;i++)
    cout <<endl;
    for(i = 0; i < len; i ++)
    {
        for(j = 0; j < wid; j ++)
        {
            cout <<maze[i][j]<<" ";
        }
        cout <<endl;
    }
    return 0;
}
