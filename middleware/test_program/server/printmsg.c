#include <stdio.h>
#include "msg.h" /*  msg.h generated by rpcgen */

extern int* printmessage_1_svc(char **msg, struct svc_req *req)
    
{
       static int result; /*  must be static! */
       FILE *f;
        
       f = fopen("/dev/console", "w");
       if (f == (FILE *)NULL) {
           result = 0;
           return (&result);
           }
       fprintf(f, "%s\n", *msg);
       printf("%s\n",*msg);
       fclose(f);
       result = 1;
       return (&result);
}
           
