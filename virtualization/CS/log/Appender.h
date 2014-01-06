/*
 * =====================================================================================
 *
 *       Filename:  Appender.h
 *
 *    Description:  ��־������ӿ�
 *
 *        Version:  1.0
 *        Created:  04/24/2011 12:02:05 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shi Wei (sw), shiwei2012@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */


#ifndef COMMON_LOG_APPENDER_H_
#define COMMON_LOG_APPENDER_H_

#include <cstddef>
#include <stdarg.h>
#include <string>

#include "LogLevel.h"
#include "../sys/noncopyable.h"

/**
 * @brief ��־������ӿ���
 */
class Appender : public noncopyable {
    public:
        /**
         * @brief ��������
         */
        virtual ~Appender() {};

        /**
         * @brief ��־�������ʼ��
         *
         * @return 
         *      - 0 ��ʼ���ɹ�
         *      - -1 ��ʼ��ʧ��
         */
        virtual int init() {
            return 0;
        }

        /**
         * @brief ��¼��־
         *
         * @param loggerName ��־������
         * @param level ��־����
         * @param fmt ��־��ʽ
         * @param ap ��־����
         * @param file ������־��Դ�ļ���������DEBUG��
         * @param line ������־��Դ���кţ�������DEBUG��
         * @param function ������־��Դ�����ں�������������DEBUG��
         */
        
        virtual void log(
                std::string loggerName, 
                LogLevel level, 
                const char *fmt, 
                va_list ap,
                const char *file = NULL,
                int line = 0,
                const char *function = NULL) = 0;

        /**
         * @brief ��־���������
         */
        virtual void destroy() {}

    protected:
        /**
         * @brief ��ȡ��ǰʱ�䣬��ʽΪ2011-04-24 14:55:35
         *
         * @return ʱ���ִ�
         */
        std::string getTimeNow();

        /**
         * @brief ��ȡ���̺ŵ��ַ�����ʾ
         *
         * @return 
         */
        std::string getPID();

        /**
         * @brief ��ȡ�̺߳ŵ��ַ�����ʾ
         *
         * @return 
         */
        std::string getTID();

        /**
         * @brief ��ȡ���̺ź��̺߳ŵ��ַ�����ʾ
         *
         * @return 
         */
        std::string getPIDAndTID();

        /**
         * @brief ��ȡ��־�����Ӧ����־�����ַ�����ʾ
         *
         * @return ��־�����ִ�
         */
        std::string getLogLevelString(LogLevel level);
};

#endif  // COMMON_LOG_APPENDER_H_

