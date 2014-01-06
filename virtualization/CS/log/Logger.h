/*
 * =====================================================================================
 *
 *       Filename:  Logger.h
 *
 *    Description:  ��־��
 *
 *        Version:  1.0
 *        Created:  04/24/2011 12:37:53 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shi Wei (sw), shiwei2012@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef COMMON_LOG_LOGGER_H_
#define COMMON_LOG_LOGGER_H_

#include <cstddef>
#include <stdarg.h>
#include <list>
#include <string>

#include "../sys/noncopyable.h"
#include "LogLevel.h"

class Appender;
class LoggerFactory;

/**
 * @brief ��־�ඨ��
 */
class Logger : public noncopyable {
    friend class LoggerFactory;
    public:
        /**
         * @brief ���ش���
         *
         * @param fmt ��־��ʽ
         * @param ...
         */
        void fatal(const char *fmt, ...);

        /**
         * @brief ����
         *
         * @param fmt ��־��ʽ
         * @param ...
         */
        void error(const char *fmt, ...);

        /**
         * @brief ����
         *
         * @param fmt ��־��ʽ
         * @param ...
         */
        void warn(const char *fmt, ...);

        /**
         * @brief ��ͨ��Ϣ
         *
         * @param fmt ��־��ʽ
         * @param ...
         */
        void info(const char *fmt, ...);

        /**
         * @brief ������Ϣ
         *
         * @param file ������־��Դ�ļ�
         * @param line ������־��Դ���к�
         * @param function ������־��Դ�������ں�������
         * @param fmt ��־��ʽ
         * @param ... ��־����
         */
        void debug(
                const char *file,
                int line,
                const char *function,
                const char *fmt, ...);

        /**
         * @brief ������Ϣ
         *
         * @param fmt ��־��ʽ
         * @param ...
         */
        void trace(const char *fmt, ...);

    private:
        Logger();  // can't new

        /**
         * @brief ��������
         */
        virtual ~Logger();


        /**
         * @brief ���õ�ǰ��־���𣬵��ڴ˼������־��������¼
         *
         * @param level
         */
        void setLevel(LogLevel level);

        /**
         * @brief ���һ����־�����
         *
         * @param apdr
         */
        void addAppender(Appender *apdr);

        /**
         * @brief ����Logger������
         *
         * @param name
         */
        void setName(const std::string &name);

        /**
         * @brief ִ�о�����־��¼����
         *
         * @param level ��־����
         * @param fmt ��־��ʽ
         * @param ap ��־����
         * @param file  ������־��Դ�ļ���������DEBUG)
         * @param line  ������־��Դ���кţ�������DEBUG��
         * @param function ������־��Դ�������ں������ƣ�������DEBUG)
         */
        void doLog(
                LogLevel level, 
                const char *fmt, 
                va_list ap, 
                const char *file = NULL,
                int line = 0,
                const char *function = NULL);

    private:
        LogLevel m_Level;  // log level
        std::list<Appender *> m_AppenderList;  // list of Appenders
        std::string m_Name;  // Logger name
};
#endif  // COMMON_LOG_LOGGER_H_

