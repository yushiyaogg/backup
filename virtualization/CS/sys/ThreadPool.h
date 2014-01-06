/*
 * =====================================================================================
 *
 *       Filename:  ThreadPool.h
 *
 *    Description:  �̳߳�ʵ��
 *
 *        Version:  1.0
 *        Created:  04/26/2011 11:11:25 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shi Wei (sw), shiwei2012@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef COMMON_SYS_THREADPOOL_H_
#define COMMON_SYS_THREADPOOL_H_

#include <list>

#include "Thread.h"

// �������߳���
#define THREAD_MAX_IDLE_DEFAULT 15
// ����߳�����
#define THREAD_MAX_TOTAL_DEFAULT 60

/**
 * @brief �̳߳�������ӿ�
 */
class ThreadPoolWorkItem {
    public:
        ThreadPoolWorkItem() {}
        virtual ~ThreadPoolWorkItem() {}

        /**
         * @brief ��ִ�о���ҵ��ǰ�Ĺ�������
         *
         * @return 
         */
        virtual int preProcess() {
            return 0;
        }

        /**
         * @brief ʵ�ִ˷�����ִ�о���ҵ��
         *
         * @return 
         */
        virtual int process() = 0;

        /**
         * @brief ִ�о���ҵ���Ĺ�������
         *
         * @return 
         */
        virtual int postProcess() {
            return 0;
        }
};

/**
 * @brief �̳߳�ʵ��
 */
class ThreadPool {
    public:
        /**
         * @brief ���캯��
         *
         * @param maxIdle �������߳���
         * @param maxTotal ����߳�����
         */
        ThreadPool(int maxIdle = THREAD_MAX_IDLE_DEFAULT,
                int maxTotal = THREAD_MAX_TOTAL_DEFAULT);

        ~ThreadPool();

        /**
         * @brief �·������̳߳أ���д��m_hWriteHandle
         *
         * @param pWorkItem �̳߳�����ָ��
         *
         * @return 
         *      - 0 �ɹ�
         *      - ... ʧ�ܵ�errno
         */
        int postRequest(ThreadPoolWorkItem *pWorkItem);

        /**
         * @brief �����̳߳ؾ������m_hWriteHandle
         *
         * @return �̳߳ؾ��
         */
        int getHandle() const;

        /**
         * @brief �����̳߳�
         *
         * @return 
         */
        int start();

        /**
         * @brief ֹͣ�̳߳�
         *
         * @return 
         */
        int stop();

    protected:
        //can't copy
        ThreadPool(const ThreadPool &tp);
        ThreadPool& operator=(const ThreadPool &tp);

        /**
         * @brief �̳߳���ִ���¼�������߳�
         */
        class EventHandlerThread : public Thread {
            public:
                EventHandlerThread(ThreadPool *pool);

            protected:
                virtual void run();
                
            private:
                ThreadPool *m_pThreadPool;
        };

        /**
         * @brief �̳߳��յ����������˳�
         */
        class ThreadExitWorkItem : public ThreadPoolWorkItem {
            public:
                int process();
        };

    private:
        int m_hReadHandle;  // �ܵ�����
        int m_hWriteHandle;  // �ܵ�д��
        int m_nMaxIdle;
        int m_nMaxTotal;
        std::list<Thread *> m_ThreadList;
        Mutex m_Mutex;  // to protect m_ThreadList;
};

#endif  // COMMON_SYS_THREADPOOL_H_

