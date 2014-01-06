/*
 * =====================================================================================
 *
 *       Filename:  connmysql-preprocess1.cpp
 *
 *    Description:  How to communicate with mysql use Connector/C to execute insert
 *                  operation  
 *
 *        Version:  1.0
 *        Created:  01/10/2013 09:18:53 PM
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
#include <cstring>
#include <unistd.h>
#include <stdlib.h>
#define STRING_SIZE 50
#define INSERT_SAMPLE "INSERT INTO Students(id,name) VALUES(?,?)"

int main(void)
{
    MYSQL mysql;
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[2];
    char id[STRING_SIZE];
    char name[STRING_SIZE];
    unsigned int paramcount;
    unsigned long id_length;
    unsigned long name_length;
    my_ulonglong affected_rows;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","root","uestc8020","test",0,NULL,0))
    {
        fprintf(stderr,"connect error:%s\n",mysql_error(&mysql));
        exit(0);
    }
    stmt=mysql_stmt_init(&mysql);
    if(!stmt)
    {
        fprintf(stderr,"mysql_stmt_init failed:%s\n",mysql_stmt_error(stmt));
        exit(0);
    }
    if(mysql_stmt_prepare(stmt,INSERT_SAMPLE,strlen(INSERT_SAMPLE)))
    {
        fprintf(stderr,"mysql_stmt_prepare failed:%s\n",mysql_stmt_error(stmt));
        exit(0);
    }
    paramcount=mysql_stmt_param_count(stmt);
    //printf("param count is:%d\n",paramcount);
    if(2!=paramcount)
    {
        fprintf(stderr,"param count error\n");
        exit(0);
    }
    memset(bind,0,sizeof(bind));
    bind[0].buffer_type=MYSQL_TYPE_STRING;
    bind[0].buffer=(char*)id;
    bind[0].buffer_length=STRING_SIZE;
    bind[0].is_null=0;
    bind[0].length=&id_length;
    bind[1].buffer_type=MYSQL_TYPE_STRING;
    bind[1].buffer=(char*)name;
    bind[1].buffer_length=STRING_SIZE;
    bind[1].is_null=0;
    bind[1].length=&name_length;
    if(mysql_stmt_bind_param(stmt,bind))
    {
        fprintf(stderr,"mysql bind param error:%s\n",mysql_stmt_error(stmt));
        exit(0);
    }
    strncpy(id,"uestc8020",STRING_SIZE);
    id_length=strlen(id);
    strncpy(name,"wuyu",STRING_SIZE);
    name_length=strlen(name);    
    if(mysql_stmt_execute(stmt))
    {
        fprintf(stderr,"sql execute failed:%s\n",mysql_stmt_error(stmt));
        exit(0);
    }
    printf("excute success\n");
    affected_rows=mysql_stmt_affected_rows(stmt);
    if(1!=affected_rows)
    {
        fprintf(stderr,"invalid affected rows by mysql\n");
        exit(0);
    }
    strncpy(id,"uestc8021",STRING_SIZE);
    id_length=strlen(id);
    strncpy(name,"yushiyaogg",STRING_SIZE);
    name_length=strlen(name);
    if(mysql_stmt_execute(stmt))
    {
        fprintf(stderr,"sql execute failed:%s\n",mysql_stmt_error(stmt));
        exit(0);
    }
    affected_rows=mysql_stmt_affected_rows(stmt);
    if(1!=affected_rows)
    {
        fprintf(stderr,"invaild affected rows by mysql\n");
        exit(0);
    }
    if(mysql_stmt_close(stmt))
    {
        fprintf(stderr,"stmt close error:%s\n",mysql_stmt_error(stmt));
        exit(0);
    }
    return 0;
}    
