/*
 * =====================================================================================
 *
 *       Filename:  Appender.cpp
 *
 *    Description:  ÈÕÖ¾Êä³öÆ÷
 *
 *        Version:  1.0
 *        Created:  04/24/2011 02:55:23 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shi Wei (sw), shiwei2012@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "Appender.h"

#include <cstdio>

#include <string>

#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

#include "LogLevel.h"

std::string Appender::getTimeNow() {
    time_t t;
    time(&t);  // get now time

    struct tm pt;  // parsed time
    localtime_r(&t, &pt);
    
    char time_str[30];  // time has format 2011-04-24 15:04:22
    snprintf(time_str, 30, "%04d-%02d-%02d %02d:%02d:%02d", 
            pt.tm_year + 1900,
            pt.tm_mon + 1,
            pt.tm_mday,
            pt.tm_hour,
            pt.tm_min,
            pt.tm_sec);
    return std::string(time_str);
}

std::string Appender::getLogLevelString(LogLevel level) {
    return std::string("[") + std::string(LOG_LEVEL_STR[level]) + "]";
}

std::string Appender::getPID() {
    char pid[20];

    sprintf(pid, "0x%x", getpid());

    return std::string(pid);
}

std::string Appender::getTID() {
    char tid[40];

    sprintf(tid, "0x%x", (unsigned int) pthread_self());

    return std::string(tid);
}

std::string Appender::getPIDAndTID() {
    return std::string("[") + getPID()
        + ":" + getTID() + "]";
}

void
Appender::log(std::string loggerName,LogLevel level,const char *fmt,va_list ap,const char *file,int line,const char *function)
{}

