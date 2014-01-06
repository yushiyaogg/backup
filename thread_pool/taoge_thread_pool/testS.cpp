#include "header.h"

int main()
{
//分配这个时候不包括结尾\0字符
char*m_pAddress = new char[sizeof(struct req_t*)];
memset(m_pAddress,'\0',sizeof(struct req_t*));
int len = strlen(m_pAddress);
strcpy(m_pAddress,"Hel");
cout<<"len:"<<len<<" "<<" ad"<<m_pAddress<<endl;
delete[] m_pAddress;
return 0;
}
