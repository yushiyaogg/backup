#ifndef _FILE_MAP_H_
#define _FILE_MAP_H_
/*实现文件名到fd的映射*/
#include <cstring>
#include <map>
using namespace std;
struct fileTable
{
int 	fd;
unsigned count;
};
struct Compator
{
bool operator()(const char*const &left,const char* const right)const
{
  return strcmp(left,right)<0;
}
};
class FileMap
{
public:
	static FileMap*  getInstance();
	int getFileFd(const char*);
	void traverse();
	void close(int);
	~FileMap();
private:
	FileMap();
	FileMap(const FileMap&);
	
 	map<const char*,struct fileTable&,Compator> m_mfileMap;
	
	
};

#endif
