/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _TASK_H_RPCGEN
#define _TASK_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


typedef char *pathname;

typedef struct {
	u_int file_data_len;
	char *file_data_val;
} file_data;

struct read_res {
	int ret;
	file_data data;
};
typedef struct read_res read_res;

struct write_arg {
	int fd;
	file_data data;
};
typedef struct write_arg write_arg;

struct read_arg {
	int fd;
	int length;
};
typedef struct read_arg read_arg;

struct open_arg {
	pathname name;
	int mode;
};
typedef struct open_arg open_arg;

#define PROG 0x30000001
#define VERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define my_open 0
extern  int * my_open_1(open_arg *, CLIENT *);
extern  int * my_open_1_svc(open_arg *, struct svc_req *);
#define my_read 1
extern  read_res * my_read_1(read_arg *, CLIENT *);
extern  read_res * my_read_1_svc(read_arg *, struct svc_req *);
#define my_write 2
extern  int * my_write_1(write_arg *, CLIENT *);
extern  int * my_write_1_svc(write_arg *, struct svc_req *);
#define my_close 3
extern  int * my_close_1(int *, CLIENT *);
extern  int * my_close_1_svc(int *, struct svc_req *);
extern int prog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define my_open 0
extern  int * my_open_1();
extern  int * my_open_1_svc();
#define my_read 1
extern  read_res * my_read_1();
extern  read_res * my_read_1_svc();
#define my_write 2
extern  int * my_write_1();
extern  int * my_write_1_svc();
#define my_close 3
extern  int * my_close_1();
extern  int * my_close_1_svc();
extern int prog_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_pathname (XDR *, pathname*);
extern  bool_t xdr_file_data (XDR *, file_data*);
extern  bool_t xdr_read_res (XDR *, read_res*);
extern  bool_t xdr_write_arg (XDR *, write_arg*);
extern  bool_t xdr_read_arg (XDR *, read_arg*);
extern  bool_t xdr_open_arg (XDR *, open_arg*);

#else /* K&R C */
extern bool_t xdr_pathname ();
extern bool_t xdr_file_data ();
extern bool_t xdr_read_res ();
extern bool_t xdr_write_arg ();
extern bool_t xdr_read_arg ();
extern bool_t xdr_open_arg ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_TASK_H_RPCGEN */
