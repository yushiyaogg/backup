/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "task.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif

static void
prog_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		open_arg my_open_1_arg;
		read_arg my_read_1_arg;
		write_arg my_write_1_arg;
		int my_close_1_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case my_open:
		_xdr_argument = (xdrproc_t) xdr_open_arg;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) my_open_1_svc;
		break;

	case my_read:
		_xdr_argument = (xdrproc_t) xdr_read_arg;
		_xdr_result = (xdrproc_t) xdr_read_res;
		local = (char *(*)(char *, struct svc_req *)) my_read_1_svc;
		break;

	case my_write:
		_xdr_argument = (xdrproc_t) xdr_write_arg;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) my_write_1_svc;
		break;

	case my_close:
		_xdr_argument = (xdrproc_t) xdr_int;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) my_close_1_svc;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	return;
}

int
main (int argc, char **argv)
{
	register SVCXPRT *transp;

	pmap_unset (PROG, VERS);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, PROG, VERS, prog_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (PROG, VERS, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, PROG, VERS, prog_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (PROG, VERS, tcp).");
		exit(1);
	}

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
	/* NOTREACHED */
}
