
#ifndef MOCKCPP_IS_REF_H
#define MOCKCPP_IS_REF_H

#include <mockcpp/mockcpp.h>

MOCKCPP_NS_START

//////////////////////////////////////////
template <typename T>
struct IsRef
{
	static const bool isTrue = false;
	static const bool outBoundable = false;
};

//////////////////////////////////////////
template <typename T>
struct IsRef<T&>
{
	static const bool isTrue = true;
	static const bool outBoundable = true;
};

//////////////////////////////////////////
template <typename T>
struct IsRef<const T&>
{
	static const bool isTrue = true;
	static const bool outBoundable = false;
};

//////////////////////////////////////////

MOCKCPP_NS_END


#endif 

