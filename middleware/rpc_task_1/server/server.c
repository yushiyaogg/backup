#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <rpc/rpc.h>
#include "task.h"



int* my_open_1_svc(open_arg* name,struct svc_req* UNUSED){

    static int fd;
    if(name -> mode == 0)
        fd = open(name->name,O_RDWR);
    else if(name -> mode == 1)
        fd = open(name -> name, O_RDONLY);
    else if(name -> mode == 2)
        fd = open(name -> name, O_WRONLY);

    return(&fd);
}

read_res* my_read_1_svc(read_arg* args , struct svc_req* UNusED){

    static read_res res; 
    
    char buf[4096]; 
    int size = read(args->fd,buf,args->length);

    if( size  == 0){
        res.ret = 0;
        return (&res);
    }  

    res.ret = size;
    res.data.file_data_len=size;
    res.data.file_data_val = malloc(sizeof(char) * size);
    memcpy(res.data.file_data_val , buf, size * sizeof(char));

    return (&res);
}


int* my_write_1_svc(write_arg* args, struct svc_req* UNUSED){

    static int error; 
    ssize_t written = write(args->fd,args->data.file_data_val,args->data.file_data_len);    

    error = (written != args->data.file_data_len)?
         -1: written;

    return (&error);
}

int* my_close_1_svc(int* fd, struct svc_req* UNUSED){
    static int error;
    int status = close(*fd);
    
    error = (status == 0)? 0 : -1;

    return (&error);
}
