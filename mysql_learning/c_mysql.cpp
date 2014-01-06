/*
 * =====================================================================================
 *
 *       Filename:  c_mysql.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/03/13 19:31:51
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (), 
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#include <iostream>
#include <mysql.h>
#include <stdio.h>
using namespace std;
int main()
{
    MYSQL mysql;
    MYSQL_RES *res = NULL;
    MYSQL_ROW row;
    char *query = "select * from username";
    string query1 = "create table if not exists student_list(stu_id int,stu_name varchar(30))";
    string query2 = "insert into student_list(stu_id,stu_name) values (1234,'董小池')";
    int t = 0, r = 0;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","experiment","uestc8020","exp",0,NULL,0))
    {
        cout << "error connecting to database"<<mysql_error(&mysql)<<endl;
        return -1;
    }
    t = mysql_query(&mysql,query1.c_str());
    if(t)
    {
        cout <<"error to create"<<mysql_error(&mysql)<<endl;
    }
    t = mysql_query(&mysql,query2.c_str());
    if(t)
    {
        cout << "error to insert"<<mysql_error(&mysql)<<endl;
    }
    mysql_close(&mysql);
    return 0;


}
