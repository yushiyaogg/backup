/*
 * =====================================================================================
 *
 *       Filename:  maze1.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/13/12 10:07:17
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

int maze[7][7]={
    {2,2,2,2,2,2,2},
    {2,0,0,0,0,0,2},
    {2,0,2,0,2,0,2},
    {2,0,0,2,0,0,2},
    {2,2,0,2,0,0,2},
    {2,0,0,0,0,0,2},
    {2,2,2,2,2,2,2}
};
int startI = 1, startJ = 1;
int endI = 5, endJ = 5;
int success = 0;
int visit(int positionI,int positionJ)
{
    maze[positionI][positionJ] = 1;
    if(positionI == endI&&positionJ == endJ)
    {
        success = 1;
        return success;
    }
    else
    {
       if( maze[positionI+1][positionJ] == 0)
           return visit(positionI+1,positionJ);
       if( maze[positionI][positionJ+1] == 0)
           return visit(positionI,positionJ+1);
       if( maze[positionI-1][positionJ] == 0)
           return visit(positionI-1,positionJ);
       if( maze[positionI][positionJ-1] == 0)
           return visit(positionI,positionJ-1);
       maze[positionI][positionJ] = 0;
       return success;
    }
}
int main()
{
    int i =0, j = 0;
    for(int i = 0 ; i < 7; i++)
    {
        for(int j = 0 ; j < 7 ; j ++)
        {
            cout << maze[i][j]<<" ";
        }

        cout << endl;
    }
    if(visit(startI, startJ) < 0)
    {
        cout << "no path"<<endl;
    }
    else
    {
        for(int i = 0; i< 4;i ++)
            cout <<endl;
        for(int i = 0 ; i < 7; i++)
        {
            for(int j = 0 ; j < 7 ; j ++)
            {
                cout << maze[i][j]<<" ";
            }

            cout << endl;
        }
        
    }
}
