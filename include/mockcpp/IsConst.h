
#ifndef MOCKCPP_IS_CONST_H
#define MOCKCPP_IS_CONST_H

#include <mockcpp/mockcpp.h>

MOCKCPP_NS_START

/////////////////////////////////////
template <typename T>
struct IsConst
{
	static const bool isTrue = false;
};

template <typename T>
struct IsConst<const T>
{
	static const bool isTrue = true;
};

template <typename T>
struct IsConst<const T&>
{
	static const bool isTrue = true;
};

MOCKCPP_NS_END


#endif 

