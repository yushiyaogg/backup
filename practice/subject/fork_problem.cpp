/*
 * =====================================================================================
 *
 *       Filename:  fork_problem.cpp
 *
 *    Description:  how many "-" will be printed?
 *
 *        Version:  1.0
 *        Created:  06/27/13 17:41:23
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (), 
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
 
int main(void)
{
       int i;
       for(i=0; i<2; i++){
       fork();
       printf("-");
       }    
       return 0;
}
