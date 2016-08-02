
#ifndef __MOCKCPP_H
#define __MOCKCPP_H


#if !defined(MOCKCPP_NO_NAMESPACE) || (MOCKCPP_NO_NAMESPACE == 0)
# define MOCKCPP_NS mockcpp
# define MOCKCPP_NS_START namespace MOCKCPP_NS {
# define MOCKCPP_NS_END }
# define USING_MOCKCPP_NS using namespace MOCKCPP_NS;
#else
# define MOCKCPP_NS 
# define MOCKCPP_NS_START 
# define MOCKCPP_NS_END 
# define USING_MOCKCPP_NS 
#endif

#ifdef _MSC_VER
# define MOCKCPP_EXPORT __declspec(dllexport)
#else
# define MOCKCPP_EXPORT 
#endif


#if  ( defined (__LP64__) \
    || defined (__64BIT__) \
    || defined (_LP64) \
    || ((defined(__WORDSIZE)) && (__WORDSIZE == 64)) \
	|| defined(WIN64))

#define BUILD_FOR_X64 1
#define BUILD_FOR_X86 0

#else	

#define BUILD_FOR_X64 0
#define BUILD_FOR_X86 1

#endif

#endif // __MOCKCPP_H

