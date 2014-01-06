/*
 * =====================================================================================
 *
 *       Filename:  LoggerFactory.cpp
 *
 *    Description:  ��־������
 *
 *        Version:  1.0
 *        Created:  04/24/2011 05:34:53 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shi Wei (sw), shiwei2012@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "LoggerFactory.h"

#include <cstdio>
#include <cstdlib>

#include <string>
#include <utility>

#include "LogLevel.h"
#include "ConsoleAppender.h"

// logger map
std::map<std::string, Logger *> LoggerFactory::m_LoggerMap;

LoggerFactory::LoggerFactory() {
    // init ROOT Logger
    Logger *rootLogger = new Logger();
    rootLogger->setName("ROOT");
    rootLogger->setLevel(LOG_DEBUG);
    
    Appender *p_Appender = new ConsoleAppender();
    if (p_Appender->init() != 0) {
        fprintf(stderr, "Error occurred while initializing the ROOT logger. Program exited.\n");
        exit(1);
    }
    
    rootLogger->addAppender(p_Appender);

    m_LoggerMap.insert(std::pair<std::string, Logger *>("ROOT", rootLogger));
}

LoggerFactory::~LoggerFactory() {
    // ��������Logger
    
}

Logger* LoggerFactory::getRootLogger() {
    return m_LoggerMap["ROOT"];
}

void
LoggerFactory::clear()
{
	for (std::map<std::string, Logger *>::iterator it = m_LoggerMap.begin();
            it != m_LoggerMap.end();
            ++it) 
    {
        delete (*it).second;
        //m_LoggerMap.erase(it);
    }
}
