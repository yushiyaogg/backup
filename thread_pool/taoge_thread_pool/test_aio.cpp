#include "aio.h"

int main(){
	struct req_t*req;
	aio_read(1,req,1,1);
	return 0;
}
