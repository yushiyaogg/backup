/*
 * =====================================================================================
 *
 *       Filename:  connmysql-preprocess.cpp
 *
 *    Description:  How to use C connector to communicate with mysql and 
 *                  use C preprocess API
 *
 *        Version:  1.0
 *        Created:  01/10/2013 03:15:46 AM
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
#define SELECT_SAMPLE "select id,status from images where name='ubuntu-11.04-desktop'"

int main(void)
{
    MYSQL mysql;
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[2];
    MYSQL_RES *meta_result;
    unsigned long length[2];
    int paramcount,columncount,rowcount;
    char id[STRING_SIZE];
    char status[STRING_SIZE];
    my_bool is_null[2];
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","root","uestc8020","glance",0,NULL,0))
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
    if(mysql_stmt_prepare(stmt,SELECT_SAMPLE,strlen(SELECT_SAMPLE)))
    {
        fprintf(stderr,"mysql_stmt_prepare failed:%s\n",mysql_stmt_error(stmt));
        exit(0);
    }
    paramcount=mysql_stmt_param_count(stmt);
    printf("param count is:%d\n",paramcount);
    if(0!=paramcount)
    {
        fprintf(stderr,"param count error\n");
        exit(0);
    }
    meta_result=mysql_stmt_result_metadata(stmt);
    if(!meta_result)
    {
        fprintf(stderr,"mysql return metadata error:%s\n",mysql_stmt_error(stmt));
        exit(0);
    }
    if(mysql_stmt_execute(stmt))
    {
        fprintf(stderr,"sql excute failed:%s\n",mysql_stmt_error(stmt));
        exit(0);
    }
    printf("excute success\n");
    memset(bind,0,sizeof(bind));
    
    bind[0].buffer_type=MYSQL_TYPE_STRING;
    bind[0].buffer=(char*)id;
    bind[0].buffer_length=STRING_SIZE;
    bind[0].is_null=&is_null[0];
    bind[0].length=&length[0];

    bind[1].buffer_type=MYSQL_TYPE_STRING;
    bind[1].buffer=(char*)status;
    bind[1].buffer_length=STRING_SIZE;
    bind[1].is_null=&is_null[1];
    bind[1].length=&length[1];

    if(mysql_stmt_bind_result(stmt,bind))
    {
        fprintf(stderr,"bind result error:%s\n",mysql_stmt_error(stmt));
        exit(0);
    }
    printf("bind result success\n");
    if(mysql_stmt_store_result(stmt))
    {
        fprintf(stderr,"store result error:%s\n",mysql_stmt_error(stmt));
        exit(0);
    }
    printf("store result success\n");
    while(!mysql_stmt_fetch(stmt))
    {
        printf("image id:%s\n",id);
        printf("image status:%s\n",status);
    }
    mysql_free_result(meta_result);
    if(mysql_stmt_close(stmt))
    {
        fprintf(stderr,"stmt close error:%s\n",mysql_stmt_error(stmt));
        exit(0);
    }
    return 0;
}    
