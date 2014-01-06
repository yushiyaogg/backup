#include "FileMap.h"
#include "header.h"

int main()
{
    int fd;
 FileMap *pFile = FileMap::getInstance();
 for(;;)
    {
 fd = pFile->getFileFd("rr");
 if(fd<0)
 cout<<"fd:"<<strerror(errno)<<endl;
 else cout<<"fd:"<<fd<<endl;
    }
 pFile->traverse();
 pFile->close(fd);  
 return 0;
}
