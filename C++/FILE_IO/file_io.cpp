/*
 * =====================================================================================
 *
 *       Filename:  file_io.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/21/13 15:38:12
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (), 
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
int main()
{
    string name = "yushiyao";
    int nt = 12;
    int nc = 12;
    ofstream outfile("data");
    if(!outfile)
    {
        cerr << "open outfile error" <<endl;
    }
    outfile << name << nt << nc<<endl;
}
