/*
 * =====================================================================================
 *
 *       Filename:  Singleton.h
 *
 *    Description:  ����ģ����
 *
 *        Version:  1.0
 *        Created:  04/23/2011 02:04:51 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (sw), shiwei2012@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef COMMON_SYS_SINGLETON_H_
#define COMMON_SYS_SINGLETON_H_

#include <cstddef>

#include <pthread.h>

/**
 * @brief ����ģ����
 *
 * @tparam T
 */
template <typename T>
class Singleton {
    public:
        /**
         * @brief ��������
         */
        virtual ~Singleton() {}

        /**
         * @brief ����Ψһʵ��
         *
         * @return ָ��ʵ����ָ��
         */
        static T* getInstance() {
            pthread_once(&m_InstanceFlag, &Singleton::initInstance);
            return m_pInstance;
        }

    protected:
        // can't new
        Singleton() {}

    private:
        static pthread_once_t m_InstanceFlag;  // to protect m_pInstance
        static T* m_pInstance;  // singleton

    private:
        // can't copy
        Singleton(const Singleton &s);
        Singleton& operator=(const Singleton &s);

        // init m_pInstance
        static void initInstance() {
            m_pInstance = new T();
        }
};

template <typename T>
pthread_once_t Singleton<T>::m_InstanceFlag = PTHREAD_ONCE_INIT;

template <typename T>
T* Singleton<T>::m_pInstance = NULL;

#endif  // COMMON_SYS_SINGLETON_H_

