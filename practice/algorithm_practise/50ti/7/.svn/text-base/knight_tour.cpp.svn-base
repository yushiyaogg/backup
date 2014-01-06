/*
 * =====================================================================================
 *
 *       Filename:  knight_tour.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/13/12 16:48:45
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
int board[8][8]= {0};

int occupy(int x, int y)
{
    if(x>7||x<0||y > 7||y < 0)
        return 0;
    if(board[x][y] > 0)
        return 1;
    else
        return 0;
}
int caculate_step(int x, int y)
{
    if(board[x][y] != 0)
        return -1;
   if(x > 5)//x ==6orx==7
    {
        if(x == 7)//x==7
        {
            if(y > 7||y < 0)
                return -1;
            else if(y ==0 ||y == 7)
            {
                return 2- (occupy(x+2,y-1)+occupy(x+2,y+1)+occupy(x-2,y-1)+occupy(x-2,y+1)+occupy(x+1,y-2)+occupy(x+1,y+2)+occupy(x-1,y-2)+occupy(x-1,y+2));
            }
            else if(y == 1 or y ==6)
                return 3- (occupy(x+2,y-1)+occupy(x+2,y+1)+occupy(x-2,y-1)+occupy(x-2,y+1)+occupy(x+1,y-2)+occupy(x+1,y+2)+occupy(x-1,y-2)+occupy(x-1,y+2));
            else
                return 4- (occupy(x+2,y-1)+occupy(x+2,y+1)+occupy(x-2,y-1)+occupy(x-2,y+1)+occupy(x+1,y-2)+occupy(x+1,y+2)+occupy(x-1,y-2)+occupy(x-1,y+2));
        }
        else if(x == 6)
        {
            if(y > 7||y< 0)
                return -1;
            else if(y == 0||y == 7)
                return 3- (occupy(x+2,y-1)+occupy(x+2,y+1)+occupy(x-2,y-1)+occupy(x-2,y+1)+occupy(x+1,y-2)+occupy(x+1,y+2)+occupy(x-1,y-2)+occupy(x-1,y+2));
            else if(y == 1||y == 6)
                return 4- (occupy(x+2,y-1)+occupy(x+2,y+1)+occupy(x-2,y-1)+occupy(x-2,y+1)+occupy(x+1,y-2)+occupy(x+1,y+2)+occupy(x-1,y-2)+occupy(x-1,y+2));
            else 
                return 6- (occupy(x+2,y-1)+occupy(x+2,y+1)+occupy(x-2,y-1)+occupy(x-2,y+1)+occupy(x+1,y-2)+occupy(x+1,y+2)+occupy(x-1,y-2)+occupy(x-1,y+2));
        }
        else
            return -1;
    
    }
    else if(x < 2)//x==1orx==0
    {
        if(x == 0)//x== 0
        {
            if(y > 7||y < 0)
                return -1;
            else if(y ==0 ||y == 7)
                return 2- (occupy(x+2,y-1)+occupy(x+2,y+1)+occupy(x-2,y-1)+occupy(x-2,y+1)+occupy(x+1,y-2)+occupy(x+1,y+2)+occupy(x-1,y-2)+occupy(x-1,y+2));
            else if(y == 1 or y ==6)
                return 3- (occupy(x+2,y-1)+occupy(x+2,y+1)+occupy(x-2,y-1)+occupy(x-2,y+1)+occupy(x+1,y-2)+occupy(x+1,y+2)+occupy(x-1,y-2)+occupy(x-1,y+2));
            else
                return 4- (occupy(x+2,y-1)+occupy(x+2,y+1)+occupy(x-2,y-1)+occupy(x-2,y+1)+occupy(x+1,y-2)+occupy(x+1,y+2)+occupy(x-1,y-2)+occupy(x-1,y+2));
        
        }
        else if(x == 1)
        {
            if(y > 7||y < 0)
                return -1;
            else if(y == 0||y == 7)
                return 3- (occupy(x+2,y-1)+occupy(x+2,y+1)+occupy(x-2,y-1)+occupy(x-2,y+1)+occupy(x+1,y-2)+occupy(x+1,y+2)+occupy(x-1,y-2)+occupy(x-1,y+2));
            else if(y == 1||y == 6)
                return 4- (occupy(x+2,y-1)+occupy(x+2,y+1)+occupy(x-2,y-1)+occupy(x-2,y+1)+occupy(x+1,y-2)+occupy(x+1,y+2)+occupy(x-1,y-2)+occupy(x-1,y+2));
            else 
                return 6- (occupy(x+2,y-1)+occupy(x+2,y+1)+occupy(x-2,y-1)+occupy(x-2,y+1)+occupy(x+1,y-2)+occupy(x+1,y+2)+occupy(x-1,y-2)+occupy(x-1,y+2));
        }
        else
            return -1;
    }
    else//x==2 3 4 5 
    {
        if(y >7||y<0)
            return -1;
        if(y == 0||y == 7) 
            return 4- (occupy(x+2,y-1)+occupy(x+2,y+1)+occupy(x-2,y-1)+occupy(x-2,y+1)+occupy(x+1,y-2)+occupy(x+1,y+2)+occupy(x-1,y-2)+occupy(x-1,y+2));
        if(y ==1|| y == 6)
            return 6- (occupy(x+2,y-1)+occupy(x+2,y+1)+occupy(x-2,y-1)+occupy(x-2,y+1)+occupy(x+1,y-2)+occupy(x+1,y+2)+occupy(x-1,y-2)+occupy(x-1,y+2));
        else
            return 8- (occupy(x+2,y-1)+occupy(x+2,y+1)+occupy(x-2,y-1)+occupy(x-2,y+1)+occupy(x+1,y-2)+occupy(x+1,y+2)+occupy(x-1,y-2)+occupy(x-1,y+2));
    }

}

int minimun(int *ptr,int len)
{
    int index = 0;
    int temp;
    temp = 9;
    for(int i = 0; i < len;i++)
    {
        if(*(ptr + i) < 0)
            continue;
        if(temp > *(ptr + i))
        {
            index = i;
            temp = *(ptr + i);
        }
    }
    if (temp ==-1)
        cout << "error"<<endl;
    return index;
}
int tour(int x,int y)
{
    int _count = 64;
    int step[8] = {-1,-1,-1,-1,-1,-1,-1,-1};
    int index;
    while(_count > 0)
    {
        board[x][y] = 65 - _count;
        step[0] = caculate_step(x+1,y+2);
        step[1] = caculate_step(x+1,y-2);
        step[2] = caculate_step(x-1,y+2);
        step[3] = caculate_step(x-1,y-2);
        step[4] = caculate_step(x+2,y+1);
        step[5] = caculate_step(x+2,y-1);
        step[6] = caculate_step(x-2,y+1);
        step[7] = caculate_step(x-2,y-1);
        index = minimun(step,8);
        if(index == 0)
        {
            x = x+1;
            y = y+2;
        }
        else if(index == 1)
        {
            x = x+1;
            y = y-2;
        }
        else if(index == 2)
        {
            x = x-1;
            y = y+2;
        }
        else if(index == 3)
        {
            x = x-1;
            y = y-2;
        }
        else if(index == 4)
        {
            x = x+2;
            y = y+1;
        }
        else if(index == 5)
        {
            x = x+2;
            y = y-1;
        }
        else if(index == 6)
        {
            x = x-2;
            y = y+1;
        }
        else if(index == 7)
        {
            x = x-2;
            y = y-1;
        }
        else 
        {
            cout <<"error"<<endl;
            return -1;
        }
        for(int i = 0; i < 7; i++)
        {
            step[i] = -1;
        }
            _count--;
        

    }
}

int main()

{
    for(int i = 0; i< 8;i++)
    {
        for(int j = 0; j < 8;j ++)
            cout<< board[i][j]<<"     ";
        cout <<endl;
    }
    tour(5,3) ;  
   cout <<endl; 
    for(int i = 0; i< 8;i++)
    {
        for(int j = 0; j < 8;j ++)
            cout<< board[i][j]<<"     ";
        cout <<endl;
    }
}
