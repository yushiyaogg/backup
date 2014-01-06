/*
 * =====================================================================================
 *
 *       Filename:  Worker.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/14/2013 02:35:46 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (), 
 *        Company:  NDSL UESTC
 *
 * =====================================================================================
 */
#ifndef _WORKER_H
#define _WORKER_H

#include "sys/ThreadPool.h"

class Woker:public ThreadPoolWorkItem
{
    public:
        Woker();
        int process();
        int postprocess();

        int state;
        MsgHeader msgheader;
        string msg;
        
                
}
#endif
