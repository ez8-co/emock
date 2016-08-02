
#ifndef __MOCKCPP_EQUALITY_UTIL_H
#define __MOCKCPP_EQUALITY_UTIL_H

#include <mockcpp/mockcpp.h>

#include <string.h>

MOCKCPP_NS_START

template <typename T>
bool isEqualComparison(const T &left, const T &right)
{
  return left == right;
}

inline
bool isEqualComparison(const char* left, const char* right)
{
	return !::strcmp(left, right);
}

MOCKCPP_NS_END

#endif // __MOCKCPP_EQUALITY_UTIL_H

