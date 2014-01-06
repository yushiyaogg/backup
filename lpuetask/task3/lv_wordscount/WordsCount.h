#ifndef _WORDSCOUNT_H_
#define _WORDSCOUNT_H_

#include <map>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class WordsCount
{
public:
	WordsCount();
	~WordsCount();

	void input(string pathname, streamoff start, streamoff end);
	void count();
	string getOneItem();
	
	
	

private:
	string formatWord(string& str);
	map<string, int> m_wordsMap;
	string m_sPathname;
	streamoff m_start;
	streamoff m_end;
	streamoff m_curr;

	map<string, int>::iterator m_iter;
	bool m_bIsFirstToGetItem;
		
};

#endif
