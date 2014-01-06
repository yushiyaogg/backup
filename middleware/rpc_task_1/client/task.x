typedef string pathname<256>;
typedef opaque file_data<4096>;


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

struct open_arg{
    pathname name;
    int mode;/*0---read&write  1----read only   2----write only*/
};
program PROG{
    version VERS{
       /* void SFO_NULL(void) = 0;*/
        int my_open(open_arg) = 0;
        read_res my_read(read_arg) = 1;
        int my_write(write_arg) = 2;
        int my_close(int fd) = 3;
    }= 1;
}=0x30000001;
