/*
 * =====================================================================================
 *
 *       Filename:  Level.h
 *
 *    Description:  ��־����
 *
 *        Version:  1.0
 *        Created:  04/24/2011 01:05:25 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shi Wei (sw), shiwei2012@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef COMMON_LOG_LOGLEVEL_H_
#define COMMON_LOG_LOGLEVEL_H_

/**
 * @brief ��־����
 */
enum _LogLevel {
    LOG_TRACE = 0,
    LOG_DEBUG = 1,
    LOG_INFO = 2,
    LOG_WARN = 3,
    LOG_ERROR = 4,
    LOG_FATAL = 5,
    LOG_NOLOG = 100  // ����¼�κ���־
};

typedef _LogLevel LogLevel;

// ��־������ַ�����ʾ
#define LOG_FATAL_STR "FATAL"
#define LOG_ERROR_STR "ERROR"
#define LOG_WARN_STR "WARN "
#define LOG_INFO_STR "INFO "
#define LOG_DEBUG_STR "DEBUG"
#define LOG_TRACE_STR "TRACE"

// ��־�����ִ����飬����ʹ��Level������
static const char* LOG_LEVEL_STR[] = {
    LOG_TRACE_STR,
    LOG_DEBUG_STR,
    LOG_INFO_STR,
    LOG_WARN_STR,
    LOG_ERROR_STR,
    LOG_FATAL_STR
};

#endif  // COMMON_LOG_LOGLEVEL_H_

