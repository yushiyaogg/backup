/*
 * =====================================================================================
 *
 *       Filename:  printmsg.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/05/12 15:12:44
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (), 
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#include <stdio.h>
#include "msg.h"
main(int argc, char **argv)
{
    CLIENT *clnt;
    int *result;
    char *server;
    char *message;

    if(argc != 3)
    {
        fprintf(stderr,"usage:%s host message\n",argv[0]);
        exit(1);
    }
    server = argv[1];
    message = argv[2];

    clnt = clnt_create(server, MESSAGEPROG, PRINTMESSAGEVERS, "tcp");
    if(clnt == (CLIENT *) NULL)
    {
        clnt_pcreateerror(server);
        printf("error\n");
        exit(1);
    }
    result = printmessage_1(&message,clnt);
    if(result == (int *)NULL)
    {
        clnt_perror(clnt,server);
        exit(1);
    }
    if(*result == 0){
        fprintf(stderr,"%s: could not print your message\n",server);
        clnt_destroy(clnt);
        exit(0);
    }
    else
        printf("result : %d\n", &result);

}
