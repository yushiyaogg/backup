/*
 * =====================================================================================
 *
 *       Filename:  conv.h
 *
 *    Description:  ����ת������
 *
 *        Version:  1.0
 *        Created:  2011-04-28 11:41:12
 *  Last Modified:  2011-04-28 11:41:12
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shi Wei (sw), shiwei2012@gmail.com
 *        Company:  NDSL UESTC
 *
 * =====================================================================================
 */

#ifndef COMMON_UTIL_CONV_H_
#define COMMON_UTIL_CONV_H_

#include <sstream>

namespace util {
    namespace conv {
        /**
         * @brief ����ת��ģ��
         *
         * @tparam D Ŀ������
         * @tparam S Դ����
         * @param s Դ����ֵ
         *
         * @return Ŀ������ֵ
         */
        template <typename D, typename S>
        D conv(const S &s);

    }
}  // namespace util

template <typename D, typename S>
D util::conv::conv(const S &s) {
    std::stringstream ss;
    ss << s;
    D d;
    ss >> d;
    return d;
}

#endif  // COMMON_UTIL_CONV_H_

