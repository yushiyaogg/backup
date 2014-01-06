#include "FileMap.h"
#include "header.h"
#include <sys/types.h>
#include <sys/stat.h>
FileMap::FileMap()
{

}
FileMap* FileMap::getInstance()
{
	static FileMap fileMap;
	return &fileMap;
}
int FileMap::getFileFd(const char* filename)
{
	int fd=-1;
	struct fileTable *file;
	if(NULL==filename||0==strlen(filename)) return -1;
  /*    
    for(map<const char*,struct fileTable&>::iterator it=m_mfileMap.begin();
            it!=m_mfileMap.end();it++)
     if(strcmp(filename,it->first)==0)
     {
        (it->second).count++;
        fd = (it->second).fd;
        return fd;
     }
     */
    map<const char*,struct fileTable&>::iterator it = m_mfileMap.find(filename);
    if(it!=m_mfileMap.end()){

        (it->second).count++;
        return (it->second).fd;
        
    }
	 fd = open(filename,O_RDWR|O_CREAT,S_IRWXU|S_IRWXG|S_IROTH);
	 if(fd<0) 
     {
        cerr<<"open file error:"<<strerror(errno)<<endl;
    return -1;
     } 
	int length = strlen(filename);
	 char *name = new char[length+1];
     file=new struct fileTable;
	 bzero(name,length+1);
	memcpy(name,filename,length);
	file->fd = fd;
	file->count = 1;
	bool flag = m_mfileMap.insert(pair<const char*,struct fileTable&>(name,*file)).second;
	if(!flag)
	{
	 cerr<<"create file:"<<name<<" error:"<<strerror(errno)<<endl;
	 return -1;
	}
		return fd;
}
void FileMap::traverse()
{
 for(map<const char*,struct fileTable&>::iterator it=m_mfileMap.begin();it!=m_mfileMap.end();
	it++)
 cout<<"filename:"<<it->first<<" fd:"<<(it->second).fd<<endl;
}

void FileMap::close(int fd)
{
	struct fileTable* file;
	for(map<const char*,struct fileTable&>::iterator it=m_mfileMap.begin();
		it!=m_mfileMap.end();it++)
	{
		file = &it->second;
		if(file->fd==fd) //找到了fd
		{
		  if(!file->count--) //如果引用计数为0,就删除该打开文件
		  {
			 delete[] it->first;
			 delete file;
			 m_mfileMap.erase(it);
			 close(fd);
			 return;
		  }
		}
	}
}

FileMap::~FileMap()
{
  for(map<const char*,struct fileTable&>::iterator it=m_mfileMap.begin();
	it!=m_mfileMap.end();)
  {
	delete []it->first;
    close(((it->second)).fd);
	delete &it->second;
	m_mfileMap.erase(it++);
  }
}


