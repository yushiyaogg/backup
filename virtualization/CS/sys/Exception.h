/*
 * =============================================================================
 * 
 *       Filename:  Exception.h
 * 
 *    Description:  �쳣��װ
 * 
 *        Version:  1.0
 *        Created:  2011-05-26 19:07:08
 *  Last Modified:  2011-05-26 19:07:08
 *       Revision:  none
 *       Compiler:  gcc
 * 
 *         Author:  Shi Wei (sw), shiwei2012@gmail.com
 *        Company:  NDSL UESTC
 * 
 * =============================================================================
 */

#ifndef COMMON_SYS_EXCEPTION_H_
#define COMMON_SYS_EXCEPTION_H_

#include <exception>
#include <string>
#include <ostream>

/** 
* @brief Exception�Ƕ�std::exception�ķ�װ 
*/
class Exception : public std::exception
{
public:

    Exception();

    Exception(const std::string &msg);

    Exception(const std::string &file, 
            int line);

    /**
     * @brief ���캯��
     *
     * @param file �׳��쳣��Դ�ļ���
     * @param line �׳��쳣�Ĵ�����
     */
    Exception(const std::string &msg,
            const std::string &file,
            int line);

    virtual ~Exception() throw();

    /**
     * @brief ����쳣�������
     *
     * @return 
     *      �쳣�������
     */
    virtual std::string name() const;

    /**
     * @brief ����쳣������Ϣ
     *
     * @return 
     *      �쳣������Ϣ
     */
    virtual const char* what() const throw();

    /**
     * @brief ����׳��쳣��Դ�ļ���
     *
     * @return 
     */
    std::string file() const;

    /**
     * @brief ����׳��쳣�Ĵ����к�
     *
     * @return 
     */
    int line() const;

    /**
     * @brief ��ȡ�쳣��Ϣ
     *
     * @return 
     */
    std::string message() const;

protected:
    virtual void print(std::ostream &out) const;
    
private:
    
    static const std::string m_Name;  // name of this class
    mutable std::string m_WhatMessage;  // what��Ϣ
    std::string m_Message;  // �쳣��Ϣ
    std::string m_File;  // source code file name
    int m_Line;  // source code line number
};

std::ostream& operator << (std::ostream& out, const Exception &ex);

/** 
 * @brief ��ָ���쳣
 */
class NullPointerException : public Exception
{
public:
    
    NullPointerException();
    NullPointerException(const std::string &msg);
    NullPointerException(
            const std::string &file,
            int line);
    NullPointerException(const std::string &msg,
            const std::string &file,
            int line);
    virtual ~NullPointerException() throw();

    virtual std::string name() const;

private:
    static const std::string m_Name;
};

/** 
 * @brief �Ƿ������쳣
 */
class IllegalArgumentException : public Exception
{
public:
    
    IllegalArgumentException();
    IllegalArgumentException(const std::string &msg);
    IllegalArgumentException(
            const std::string &file,
            int line);
    IllegalArgumentException(
            const std::string &msg,
            const std::string &file,
            int line);
    virtual ~IllegalArgumentException() throw();

    virtual std::string name() const;

private:

    static const std::string m_Name;
};

/** 
 * @brief ϵͳ�����쳣
 */
class SyscallException : public Exception
{
public:

    /**
     * @brief 
     *
     * @param error errno
     */
    SyscallException(int error = 0);
    SyscallException(const std::string &msg,
            int error = 0);
    SyscallException(const std::string &file,
            int line,
            int error = 0);
    SyscallException(const std::string &msg, 
            const std::string &file,
            int line,
            int error = 0);

    virtual std::string name() const;
    virtual int getErrorNo() const;

private:
    static const std::string m_Name;
    int m_Error;  // errno
};

#endif  // COMMON_SYS_EXCEPTION_H_

