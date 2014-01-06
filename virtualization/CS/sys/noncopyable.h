/*
 * =====================================================================================
 *
 *       Filename:  noncopyable.h
 *
 *    Description:  �����������Ķ��󲻿ɿ���
 *
 *        Version:  1.0
 *        Created:  04/23/2011 01:40:38 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef COMMON_SYS_NONCOPYABLE_H_
#define COMMON_SYS_NONCOPYABLE_H_

class noncopyable {
    protected:
        noncopyable() {}
        virtual ~noncopyable() {}

    private:
        // don't define these members
        noncopyable(const noncopyable &nc);
        noncopyable& operator=(const noncopyable &nc);
};

#endif  // COMMON_SYS_NONCOPYABLE_H_

