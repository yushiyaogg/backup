/*
 * =====================================================================================
 *
 *       Filename:  Logger.cpp
 *
 *    Description:  ��־��ʵ��
 *
 *        Version:  1.0
 *        Created:  04/24/2011 02:08:20 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shi Wei (sw), shiwei2012@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "Logger.h"

#include <cstddef>
#include <cstdarg>

#include <list>
#include <string>

#include "Appender.h"
#include "LogLevel.h"

Logger::Logger()
    : m_Level(LOG_DEBUG) 
{

}

Logger::~Logger() {
    // ����ÿ��Appender
    for (std::list<Appender *>::iterator it = m_AppenderList.begin();
            it != m_AppenderList.end(); 
            ++it) {
        (*it)->destroy();
        delete (*it);
        *it = NULL;
    }
    m_AppenderList.clear();
}

void Logger::setLevel(LogLevel level) {
    m_Level = level;
}

void Logger::setName(const std::string &name) {
    m_Name = name;
}

void Logger::addAppender(Appender *apdr) {
    m_AppenderList.push_back(apdr);
}

void Logger::doLog(
        LogLevel level, 
        const char *fmt, 
        va_list ap, 
        const char *file,
        int line,
        const char *function) {
    // ����־д�뵽ÿ��Appender
    /*for (std::list<Appender *>::iterator it = m_AppenderList.begin();
            it != m_AppenderList.end();
            ++it) {
        if (level == LOG_DEBUG) {  // ����ǵ�����Ϣ
            if (NULL == file || NULL == function) {
                (*it)->log(m_Name, level, fmt, ap, "NULL", line, "NULL");
            } else {
                (*it)->log(m_Name, level, fmt, ap, file, line, function);
            }
        } else {
            (*it)->log(m_Name, level, fmt, ap);
        }
    }*/
}

void Logger::fatal(const char *fmt, ...) {
    // ����趨����־�����FATAL�ͣ����¼��־
    if (LOG_FATAL >= m_Level) {
        va_list ap;

        va_start(ap, fmt);
        doLog(LOG_FATAL, fmt, ap);
        va_end(ap);
    }
}

void Logger::error(const char *fmt, ...) {
    if (LOG_ERROR >= m_Level) {
        va_list ap;

        va_start(ap, fmt);
        doLog(LOG_ERROR, fmt, ap);
        va_end(ap);
    }
}

void Logger::warn(const char *fmt, ...) {
    if (LOG_WARN >= m_Level) {
        va_list ap;

        va_start(ap, fmt);
        doLog(LOG_WARN, fmt, ap);
        va_end(ap);
    }
}

void Logger::info(const char *fmt, ...) {
    if (LOG_INFO >= m_Level) {
        va_list ap;

        va_start(ap, fmt);
        doLog(LOG_INFO, fmt, ap);
        va_end(ap);
    }
}

void Logger::debug(
        const char *file,
        int line,
        const char *function,
        const char *fmt, ...) {
    if (LOG_DEBUG >= m_Level) {
        va_list ap;

        va_start(ap, fmt);
        doLog(LOG_DEBUG, fmt, ap, file, line, function);
        va_end(ap);
    }
}

void Logger::trace(const char *fmt, ...) {
    if (LOG_TRACE >= m_Level) {
        va_list ap;

        va_start(ap, fmt);
        doLog(LOG_TRACE, fmt, ap);
        va_end(ap);
    }
}

