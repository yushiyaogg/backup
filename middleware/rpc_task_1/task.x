/**
  protocal definition of  a Simple File Operation(SFO)  protocol.
  @Author :  201121060230
  @Version:  1.0
 */
typedef string sfo_pathname<256>;
typedef opaque sfo_file_data<4096>;

enum sfo_error{
    ERR_NONE = 0,
    ERR_NO_SUCH_NAME = 1,
    ERR_READ_FAILED  = 2,
    ERR_WRITE_FAILED = 3,
    ERR_CLOSE_FAILED = 4
};

union sfo_open_res switch(sfo_error error){
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
};

struct sfo_write_arg{
    int fd;/*file descriptor*/
    sfo_file_data data;/*the data to be written*/
};

struct sfo_read_arg{
    int fd;/*file descriptor*/
    int length;/*total length need to be read*/
};

program SFO_PROG{
    version SFO_VERS{
        void SFO_NULL(void) = 0;
        sfo_open_res SFO_open(sfo_pathname) = 1;
        sfo_read_res SFO_read(sfo_read_arg) = 2;
        sfo_error SFO_write(sfo_write_arg) = 3;
        sfo_error SFO_close(int fd) = 4;
    }= 1;
}=0x30000001;
