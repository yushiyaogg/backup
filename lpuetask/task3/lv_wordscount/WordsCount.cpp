#include "WordsCount.h"

#include <algorithm>
#include <cctype>


WordsCount::WordsCount()
	:m_start(0), m_end(0), m_curr(0), m_bIsFirstToGetItem(true)
{
}

WordsCount::~WordsCount()
{
}

void WordsCount::input(string pathname, streamoff start, streamoff end)
{
	m_sPathname = pathname;
	m_start = start;
	m_curr = start;
	m_end = end;
}

void WordsCount::count()
{
	ifstream file(m_sPathname.c_str());
	file.seekg(m_start, ios::beg);
	string str;


	while(file >> str && m_curr < m_end){

		if(str == "."
			&& str == ","
			&& str == " "
            ){
			continue;
		}

		str = formatWord(str);
		++m_wordsMap[str];
		m_curr += str.size();
	}

	file.close();
}

string WordsCount::formatWord(string& str)
{
	string clearchar = ",.?!:();";
	size_t iPos;

	iPos = str.find_last_of(clearchar);
	if ( iPos != string::npos )
    {
        str = str.substr( 0 , iPos ) + str.substr( iPos + 1 , -1 );
    }

	return str;

}

string WordsCount::getOneItem()
{
	if(m_bIsFirstToGetItem){
		m_iter = m_wordsMap.begin();
		m_bIsFirstToGetItem = false;
	}

	if(m_iter != m_wordsMap.end()){
		cout << "|"<<m_iter->first <<"|"<< "\t\t\t" << m_iter->second <<endl;
		++m_iter;
		return "ok";
	}

	return "end";
}

int main(int argc, char **argv)
{
	WordsCount wc;
	wc.input(argv[1], atol(argv[2]), atol(argv[3]));
	wc.count();
	wc.count();
	while(wc.getOneItem() == "ok");
}

