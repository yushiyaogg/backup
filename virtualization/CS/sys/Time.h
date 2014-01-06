/*
 * =====================================================================================
 *
 *       Filename:  Timer.h
 *
 *    Description:  ��ʱ������ķ�װ
 *
 *        Version:  1.0
 *        Created:  04/25/2011 09:19:53 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shi Wei (sw), shiwei2012@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */


#ifndef COMMON_SYS_TIME_H_
#define COMMON_SYS_TIME_H_

#include <string>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>


/**
 * @brief ��װ��ʱ��Ĳ���
 */
class Time
{
public:

    Time();

    Time(int64_t);

    enum Clock { Realtime, Monotonic };

    /** 
     * @brief ��ȡ��ǰʱ��
     * 
     * @param clock 
     *      - Realtime: ϵͳrtcʱ��
     *      - Monotonic: ϵͳ��boost�𾭹���ʱ��
     * 
     * @return  ��ǰʱ��
     */
    static Time now(Clock clock= Realtime);

    /** 
     * @brief ����һ��ʱ�����
     * 
     * @param usec: �����ʱ��(��)
     * 
     * @return 
     */
    static Time seconds(int64_t usec);

    /** 
     * @brief ����һ��ʱ����� 
     * 
     * @param milli ����Ľ���(����)
     * 
     * @return 
     */
    static Time milliSeconds(int64_t milli);

    /** 
     * @brief ����һ��ʱ����� 
     * 
     * @param micro �����ʱ��(΢��)
     * 
     * @return 
     */
    static Time microSeconds(int64_t micro);
    
    /** 
     * @brief ��Timeת����timeval�ṹ
     * 
     * @return 
     */
    operator timeval() const;

    /** 
     * @brief ��ʱ��ת������
     * 
     * @return 
     */
    int64_t toSeconds() const;

    /** 
     * @brief ��ʱ��ת���ɺ���
     * 
     * @return 
     */
    int64_t toMilliSeconds() const;

    /** 
     * @brief ��ʱ��ת����΢��
     * 
     * @return 
     */
    int64_t toMicroSeconds() const;

    double toSecondsDouble() const;
    double toMilliSecondsDouble() const;
    double toMicroSecondsDouble() const;

    /** 
     * @brief ��ʱ��ת�����ַ���,����: 2009-10-26 10:47:47.932
     * 
     * @return 
     */
    std::string toDateTime() const;

    /** 
     * @brief ��ʱ��ת�����ַ���,����: 14543d 02:47:47.932
     * 
     * @return 
     */
    std::string toDuration() const;

    Time operator-() const
    {
        return Time(-_usec);
    }

    Time operator-(const Time& rhs) const
    {
        return Time(_usec - rhs._usec);
    }

    Time operator+(const Time& rhs) const
    {
        return Time(_usec + rhs._usec);
    }

    Time& operator+=(const Time& rhs)
    {
        _usec += rhs._usec;
        return *this;
    }

    Time& operator-=(const Time& rhs)
    {
        _usec -= rhs._usec;
        return *this;
    }

    bool operator<(const Time& rhs) const
    {
        return _usec < rhs._usec;
    }

    bool operator<=(const Time& rhs) const
    {
        return _usec <= rhs._usec;
    }

    bool operator>(const Time& rhs) const
    {
        return _usec > rhs._usec;
    }

    bool operator>=(const Time& rhs) const
    {
        return _usec >= rhs._usec;
    }

    bool operator==(const Time& rhs) const
    {
        return _usec == rhs._usec;
    }

    bool operator!=(const Time& rhs) const
    {
        return _usec != rhs._usec;
    }

    double operator/(const Time& rhs) const
    {
        return (double)_usec / (double)rhs._usec;
    }

    Time& operator*=(int rhs)
    {
        _usec *= rhs;
        return *this;
    }

    Time operator*(int rhs) const
    {
        Time t;
        t._usec = _usec * rhs;
        return t;
    }

    Time& operator/=(int rhs)
    {
        _usec /= rhs;
        return *this;
    }

    Time operator/(int rhs) const
    {
        Time t;
        t._usec = _usec / rhs;
        return t;
    }

    Time& operator*=(int64_t rhs)
    {
        _usec *= rhs;
        return *this;
    }

    Time operator*(int64_t rhs) const
    {
        Time t;
        t._usec = _usec * rhs;
        return t;
    }

    Time& operator/=(int64_t rhs)
    {
        _usec /= rhs;
        return *this;
    }

    Time operator/(int64_t rhs) const
    {
        Time t;
        t._usec = _usec / rhs;
        return t;
    }

    Time& operator*=(double rhs)
    {
        _usec = static_cast<int64_t>(static_cast<double>(_usec) * rhs);
        return *this;
    }

    Time operator*(double rhs) const
    {
        Time t;
        t._usec = static_cast<int64_t>(static_cast<double>(_usec) * rhs);
        return t;
    }

    Time& operator/=(double rhs)
    {
        _usec = static_cast<int64_t>(static_cast<double>(_usec) / rhs);
        return *this;
    }

    Time operator/(double rhs) const
    {
        Time t;
        t._usec = static_cast<int64_t>(static_cast<double>(_usec) / rhs);
        return t;
    }

private:

    int64_t _usec;
};

#endif  // COMMON_SYS_TIME_H_

