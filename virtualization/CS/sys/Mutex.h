/*
 * =====================================================================================
 *
 *       Filename:  Mutex.h
 *
 *    Description:  pthread mutex��װ
 *
 *        Version:  1.0
 *        Created:  04/25/2011 09:14:18 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shi Wei (sw), shiwei2012@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef COMMON_SYS_MUTEX_H_
#define COMMON_SYS_MUTEX_H_

#include <pthread.h>

/**
 * @brief pthread mutex�򵥷�װ
 */
class Mutex {
    //friend class Cond;
public:

    Mutex();
    ~Mutex();

    /**
     * @brief ��ȡ��
     */
    void lock() const;

    /**
     * @brief trylock
     *
     * @return �Ƿ�ɹ���ȡ��
     */
    bool tryLock() const;

    /**
     * @brief �ͷ���
     */
    void unlock() const;

    /**
     * @brief ��õײ�phtread_mutex_t���͵Ļ�������
     * �˷���ֻӦ��Cond����
     *
     * @return 
     */
    pthread_mutex_t* getPthreadMutex() const;

private:
    // can't new
    Mutex(const Mutex &mutex);
    Mutex& operator=(const Mutex &mutex);

    // ��Cond��ʵ��waitʱģ��unlock��lock
    //struct LockState
    //{
    //    pthread_mutex_t* mutex;
    //};

    //void unlock(LockState *pLS) const;
    //void lock(LockState *pLS) const;

private:
    mutable pthread_mutex_t m_Mutex;
};

#endif  // COMMON_SYS_MUTEX_H_

