/*
 * =====================================================================================
 *
 *       Filename:  connmysql-nonpre.cpp
 *
 *    Description:  Show use Connector/C to communicate with mysql
 *
 *        Version:  1.0
 *        Created:  01/10/2013 03:12:15 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  (wuyu),wuyu2012@gmail.com 
 *        Company:  NDSL UESTC
 *
 * =====================================================================================
 */

#include "mysql/mysql.h"
#include <stdio.h>

int main(void)
{
    MYSQL mysql;
    MYSQL_ROW row;
    MYSQL_RES *result;
    MYSQL_FIELD *field;
    unsigned int num_fields;
    unsigned int i;
    const char *host_info=0;
    mysql_init(&mysql);
    host_info=mysql_get_host_info(&mysql);
    printf("host info:%s\n",host_info);
    if (!mysql_real_connect(&mysql,"localhost","expriment","uestc8020","exp",0,NULL,0))
    {
        fprintf(stderr, "Failed to connect to database: Error: %s\n",
        mysql_error(&mysql));
    }
    else 
    {
        if(mysql_query(&mysql, "select stu_name from student_list where stu_id='1234'"))
            fprintf(stderr,"MYSQL QUERY failed:Error:%s\n",mysql_error(&mysql));
        else
        {
            result = mysql_use_result(&mysql);
            if(result)
            {
                num_fields = mysql_num_fields(result);
                while((field=mysql_fetch_field(result)))
                    printf("field name:%s\n",field->name);
                while ((row = mysql_fetch_row(result)))
                {
                    unsigned long *lengths;
                    lengths = mysql_fetch_lengths(result);
                    for(i = 0; i < num_fields; i++)
                    {
                        printf("[%.*s] \t",(int)lengths[i],row[i] ? row[i] : "NULL");
                    }   
                    printf("\n");
                }
                mysql_free_result(result);
            }
            else
            {
                if(mysql_errno(&mysql))
                    fprintf(stderr,"Error happened:%s\n",mysql_error(&mysql));
                else if(0==mysql_field_count(&mysql))
                    printf("Query doesn't return data\n");
            }
        }
    }
    mysql_close(&mysql);
    return 0;
}
