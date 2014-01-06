#include "header.h"
#include "Queue.h"


int main(){
   struct req_t req_arr[10],*req;
   Queue* queue = Queue::getInstance();
   for(int i=0;i<10;i++)
   {	
	req_arr[i]._req=i;
	if(queue->request(&req_arr[i])!=0)
	{
	 cerr<<"request error!"<<endl;
	}
   }
   while(!queue->isEmpty())
   {
	if((req=queue->doRequest())==NULL)
	{
	cerr <<"request error!"<<endl;
	}
	else 
	   cout<<"request num:"<<req->_req<<endl;
   }
	return 0;
}
