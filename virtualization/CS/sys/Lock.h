/*
 * =====================================================================================
 *
 *       Filename:  Lock.h
 *
 *    Description:  RAII(Resource Acquisition Is Initialization)ʵ��ģ��
 *
 *        Version:  1.0
 *        Created:  04/25/2011 09:19:53 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shi Wei (sw), shiwei2012@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef COMMON_SYS_LOCK_H_
#define COMMON_SYS_LOCK_H_

#include "Mutex.h"

/**
 * @brief ���ٽ���Դ��Guard���ڹ������е���Mutex��lock������
 * ��������������unlock������ͨ��ʵ����Lock���͵ľֲ�
 * ���������ڴ˱����������ڳ�����
 */
class Lock {
public:
    Lock(const Mutex &mutex) :
        m_Mutex(mutex)
    {
        m_Mutex.lock();
    }

    ~Lock()
    {
        m_Mutex.unlock();
    }
    
private:
    // can't copy
    Lock(const Lock&);
    Lock& operator=(const Lock&);

private:
    const Mutex &m_Mutex;
};

// ��ֹ��дΪLock(mutex)������д��Lock���͵ı�������
// ���¶��������Ժ�������������Ҳ�漴�ͷ���
// ����protocol buffer�ڲ�ʵ������һ��Lock()�������˺궨�彫ʹ�������
// ���ע�͵���������ʹ��Lockʱһ��Ҫע����������
//#define Lock(x) static_assert(false, "missing lock variable name")
//const bool MISSING_LOCK_VARIABLE_NAME = false;
//#define Lock(x) assert(MISSING_LOCK_VARIABLE_NAME);

#endif  // COMMON_SYS_LOCK_H_

