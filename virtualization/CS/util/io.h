/*
 * =====================================================================================
 *
 *       Filename:  io.h
 *
 *    Description:  IO��������
 *
 *        Version:  1.0
 *        Created:  2011-04-28 11:47:13
 *  Last Modified:  2011-04-28 11:47:13
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shi Wei (sw), shiwei2012@gmail.com
 *        Company:  NDSL UESTC
 *
 * =====================================================================================
 */


#ifndef COMMON_UTIL_IO_H_
#define COMMON_UTIL_IO_H_

#include <sys/types.h>

namespace util {
    namespace io {
        /**
         * @brief ��n�ֽ�
         *
         * @param fd ������
         * @param vptr ��Ŷ�ȡ���ݵĻ�����
         * @param n ����ȡ�ֽ���
         *
         * @return ʵ�ʶ�ȡ�ֽ���
         */
        ssize_t readn(int fd, void *vptr, size_t n);

        /**
         * @brief дn�ֽ�
         *
         * @param fd ������
         * @param vptr ��д��������
         * @param n ��д���ֽ���
         *
         * @return ʵ��д�����ֽ���
         */
        ssize_t writen(int fd, const void *vptr, size_t n);

        /**
         * @brief ��ָ�����������÷�����
         *
         * @param fd Ҫ���õ�������
         *
         * @return 
         *      -1 - ʧ��
         *      0  - �ɹ�
         */
        int setNonblock(int fd);

    }  // namespace io

} // namespace util

#endif  // COMMON_UTIL_IO_H_

