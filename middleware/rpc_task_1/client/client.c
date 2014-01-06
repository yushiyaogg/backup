#include <stdio.h>
#include <error.h>
#include "task.h"

#define SERVER "127.0.0.1"
int main(int argc , char** argv){
	pathname filename;
	int* res;
	read_res* read_res;
	write_arg write_args ;  
	read_arg args;
    open_arg arg_for_open;
	char buf[120];
	int fd;
	int* error;
	int* error_info;
	const char *str = "I am the new data to be add!\n"; 

    /*
     * open
     */
    void* cl = clnt_create(SERVER,PROG, VERS, "tcp");

    if(cl == 0){
        fprintf(stderr,"clnt_create() failed");
        exit(1);
    }
    arg_for_open.name ="/home/yushiyao/middleware/yushiyaogg";
    arg_for_open.mode = 0;
    res = my_open_1(&arg_for_open,cl);
    if(*res < 0){
       printf("open failed\n");
       exit(1); 
    }

    fd = *res;
	
    /*  
     *  write
     **/
    
     write_args.fd = fd;
    

    write_args.data.file_data_len = strlen(str);
    write_args.data.file_data_val = (char*)malloc(strlen(str) * sizeof(char));
    memcpy(write_args.data.file_data_val, str , strlen(str)* sizeof(char));
    error_info = my_write_1(&write_args,cl);

    if(*error_info < 0){
        printf("write failed");
        exit(1);
    }

    /* 
     * read
     */
    args.fd = fd;
    args.length = 120;

    read_res = my_read_1(&args,cl);

    if(read_res->ret < 0){
        printf("read failed");
        exit(1);
    }else{
        
        memcpy(buf,read_res->data.file_data_val, read_res->data.file_data_len * sizeof(char));    
        buf[read_res->data.file_data_len] = '\0';
        printf("total :  %d\n", read_res->data.file_data_len);
        puts("begin");
        puts(buf);
        puts("end");

    }

    /*
     * close
     */
    error = my_close_1(&fd , cl); 
    if(*error < 0){
        printf("close failed");
    }
    
    return 0;
}
