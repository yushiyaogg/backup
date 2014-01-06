/*
 * =====================================================================================
 *
 *       Filename:  test.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/05/13 16:20:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (), 
 *        Company:  NDSL UESTC
 *
 * =====================================================================================
 */
#include "gmr.test.pb.h"
#include <string>
#include <iostream>

using namespace std;

int main(void)
{
     gmr::test tst;
    tst.set_id(100);
    tst.set_name("handsomeryan");
//    tst.add_scores(54);
//    tst.add_scores(58);

    string teststring;
    tst.SerializeToString(&teststring);

    gmr::test tstback;
    tstback.ParseFromString(teststring);
    cout << tstback.id() << endl;
    cout << tstback.name() << endl;
    for(int i = 0; i < tstback.scores_size(); i++)
        cout << tstback.scores(i) << endl;

    return 0;
}
