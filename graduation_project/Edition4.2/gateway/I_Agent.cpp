/*
 * =====================================================================================
 *
 *       Filename:  I_Agent.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/12/12 15:04:39
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#include "I_Agent.h"

I_Agent::I_Agent(int I_fd)
{
    i_manager_agent.i_agent = this;
    d_manager_agent.i_agent = this;
    this ->fd = I_fd;
    read_len = BHS_LEN;
    Readbuff_head.new_buff(BHS_LEN);
    Readbuff = &Readbuff_head;
    read_stat = READ_MESGHEAD;

}

I_Agent::~I_Agent()
{
    if(m_epoll.epoll_delete(this) < 0)
    {
        cout<< "epoll_delete error"<<endl;
    }
    i_manager_agent.i_agent = NULL;
    close(fd);
}

int I_Agent::getfd()
{
    return fd;
}


int I_Agent::readagent()
{
    int ret;
    for(;;)
    {
        ret = I_read.read_socket(fd,Readbuff->bufferptr + Readbuff->buff_length - read_len,&read_len);

        if(ret == READ_ERROR)
        {
            cout << "read_socket error"<<endl;
            delete this;
            return -1;
        }
        else if(ret == READ_END)
        {
            cout <<"TCP disconnect"<< endl;
            delete this;
            return 0;
        }
        else if(ret == READ_BLOCK)
        {
            if(Writebuff.head!= NULL)
            {
                if(m_epoll.epoll_modify(EPOLLOUT,this) < 0)
                {
                    cout << "epoll_modify error"<<endl;
                    delete this;
                    return -1;
                }
            }
            return 0;
        }
        else if(ret == READ_SUCCESS)
        {
            if(package_head_data() < 0)
            {
                cout << "package_head_data error"<< endl;
                return -1;
            }
        }
    }

}

int I_Agent::writeagent()
{
    int ret;
    ret = I_write. write_socket(fd,&Writebuff);
    if(ret == WRITE_ERROR)
    {
        cout << "write_socket error"<< endl;
        delete this;
        return -1;
    }
    else if(ret == WRITE_BLOCK)
    {
            return 0;
    }
    else if(ret == WRITE_SUCCESS)
    {
        if(m_epoll.epoll_modify(EPOLLIN,this) < 0)
        {
            cout << "epoll_modify error"<< endl;
            return -1;
        }
        else
            return 0;
    }
}

int I_Agent::package_head_data()
{
    if(read_stat == READ_MESGHEAD)
    {
        pdu.bhs =(struct iscsi_hdr*)(Readbuff_head.bufferptr);
        pdu.Datasize = ((pdu.bhs->datalength[0]<<16) + (pdu.bhs->datalength[1]<<8) + pdu.bhs->datalength[2]);
        Readbuff_data.delete_buff();
        if(pdu.Datasize>0)
        {
            if(pdu.Datasize % 4 != 0)
            {
                Readbuff_data.new_buff(pdu.Datasize + (4 - pdu.Datasize%4));
                read_len = pdu.Datasize + (4 - pdu.Datasize % 4);
            }
            else
            {
                Readbuff_data.new_buff(pdu.Datasize );
                read_len = pdu.Datasize;
            }
            Readbuff = &Readbuff_data;
            read_stat = READ_DATA;
            return 0;
        }
    }
    if(i_manager_agent.exec() < 0) 
    {
        cout << "i_manager_agent.exec error"<<endl;
        return -1;
    }
    else
    {
        read_len = BHS_LEN;
        read_stat = READ_MESGHEAD;
        Readbuff = &Readbuff_head;
        return 0;
    }
}
