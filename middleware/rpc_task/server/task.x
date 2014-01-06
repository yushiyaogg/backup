typedef string pathname<256>;
typedef opaque file_data<4096>;

/*enum sfo_error{
    ERR_NONE = 0,
    ERR_NO_SUCH_NAME = 1,
    ERR_READ_FAILED  = 2,
    ERR_WRITE_FAILED = 3,
    ERR_CLOSE_FAILED = 4
};*/

/*union sfo_open_res switch(sfo_error error){
case ERR_NONE:
   int fd;
default:
   void;
};

union sfo_read_res switch(sfo_error error){
case ERR_NONE:
    sfo_file_data data;
default:
    void;
};*/

struct read_res 
{
    int ret;
    file_data data;
};

struct write_arg{
    int fd;/*file descriptor*/
    file_data data;/*the data to be written*/
};

struct read_arg{
    int fd;/*file descriptor*/
    int length;/*total length need to be read*/
};

program PROG{
    version VERS{
       /* void SFO_NULL(void) = 0;*/
        int my_open(pathname) = 0;
        read_res my_read(read_arg) = 1;
        int my_write(write_arg) = 2;
        int my_close(int fd) = 3;
    }= 1;
}=0x30000001;
