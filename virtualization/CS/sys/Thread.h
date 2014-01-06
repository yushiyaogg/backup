/*
 * =====================================================================================
 *
 *       Filename:  Thread.h
 *
 *    Description:  �̷߳�װ
 *
 *        Version:  1.0
 *        Created:  04/26/2011 04:51:08 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shi Wei (sw), shiwei2012@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef COMMON_SYS_THREAD_H_
#define COMMON_SYS_THREAD_H_

#include <pthread.h>

#include "Mutex.h"
#include "Time.h"

#include "../util/util.h"

/**
 * @brief �߳�ID��װ
 */
class ThreadID {
    public:
        ThreadID() {}
        explicit ThreadID(const pthread_t &tid);
        ~ThreadID() {}

        ThreadID(const ThreadID &tid);
        ThreadID& operator=(const ThreadID &tid);

        bool operator==(const ThreadID &tid);
        bool operator!=(const ThreadID &tid);

        /**
         * @brief ��ȡԭʼ������Ϊpthread_t���߳�ID
         *
         * @return pthread_t���͵��߳�ID
         */
        pthread_t getRawID() const;

    private:
        pthread_t m_TID;
};

/**
 * @brief linux�̼߳򵥷�װ�������ࣩ
 */
class Thread {
    public:
        Thread();
        virtual ~Thread();

        /**
         * @brief �����߳�
         *
         * @param stackSize ջ��С
         *
         * @return 
         */
        int start(int stackSize = 0);

        /**
         * @brief �߳��Ƿ�����ײ��߳��Ƿ�����
         *
         * @return 
         */
        bool isAlive() const;

        /**
         * @brief �ȴ��߳̽���
         *
         * @param valuePtr ���ڴ���̷߳���״̬�Ļ�������ַ
         *
         * @return 
         */
        int join(void **valuePtr = NULL);

        /**
         * @brief �����߳�
         *
         * @return 
         */
        int detach();

        /**
         * @brief �����߳�ID
         *
         * @return 
         */
        ThreadID id() const;

    protected:
        // can't copy
        Thread(const Thread &thread);
        Thread& operator=(const Thread &thread);

        /**
         * @brief ʹ�����߳��Զ�����CPU���������߳�����
         */
        static void yield();

        /**
         * @brief ʹ�����߳�˯��
         *
         * @param timeout ˯��ʱ��
         */
        static void sleep(const Time &timeout);

        /**
         * @brief ������ʵ�ִ˷�����ִ�о���ҵ��
         */
        virtual void run() = 0;

    private:
        /**
         * @brief �����б�־��Ϊfalse
         */
        void done();

        /**
         * @brief ���ݸ��߳�ִ�еĺ���
         *
         * @param arg
         *
         * @return 
         */
        static void* startHook(void *arg);
        
    protected:
        bool m_bRunning;  // �߳����б�־
        bool m_bDetached;  // ����״̬
        ThreadID m_ThreadID;  // �߳�ID
};

#endif  // COMMON_SYS_THREAD_H_

