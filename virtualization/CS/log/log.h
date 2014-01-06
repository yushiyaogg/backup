/*
 * =====================================================================================
 *
 *       Filename:  log.h
 *
 *    Description:  ��־���ͷ�ļ�
 *
 *        Version:  1.0
 *        Created:  04/24/2011 05:47:02 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shi Wei (sw), shiwei2012@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef COMMON_LOG_LOG_H_
#define COMMON_LOG_LOG_H_

#include <cstring>
#include <cerrno>

#include "LogLevel.h"
#include "Logger.h"
#include "LoggerFactory.h"

// ʹ��__VA_ARGS__����Ҫ�пɱ����
//#define DEV_LOG(logger, _fmt_, ...) logger->debug(__FILE__, __LINE__, __FUNCTION__, _fmt_, __VA_ARGS__)

#define TRACE_LOG(_fmt_, args...) LoggerFactory::getInstance()->getRootLogger()->trace(_fmt_, ##args)

#define DEBUG_LOG(_fmt_, args...) LoggerFactory::getInstance()->getRootLogger()->debug(__FILE__, __LINE__, __FUNCTION__, _fmt_, ##args)

#define INFO_LOG(_fmt_, args...) LoggerFactory::getInstance()->getRootLogger()->info(_fmt_, ##args)

#define WARN_LOG(_fmt_, args...) LoggerFactory::getInstance()->getRootLogger()->warn(_fmt_, ##args)

#define ERROR_LOG(_fmt_, args...) LoggerFactory::getInstance()->getRootLogger()->error(_fmt_, ##args)

#define FATAL_LOG(_fmt_, args...) LoggerFactory::getInstance()->getRootLogger()->fatal(_fmt_, ##args)

#endif // COMMON_LOG_LOG_H_

