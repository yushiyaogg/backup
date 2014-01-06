/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/15/12 15:21:58
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  yushiyao (), yushiyaogg@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#include "head.h"
#include "Epoll.h"
#include "S_Agent.h"

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        cout << "input the IP address"<<endl;
        return -1;
    }
    if((m_epoll.epoll_init()) < 0)
        return -1;
    S_Agent* s_agent = new S_Agent();
    if((s_agent -> connect_server(argv[1])) < 0)
    {
        cerr <<"connect_server error"<<errno<<endl;
        delete s_agent;
        return -1;
    }
    if((m_epoll.epollwait()) < 0)
    {
        delete s_agent;
        return -1;
    }
    delete s_agent;
    return 0;
}
