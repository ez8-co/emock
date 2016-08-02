
#ifndef __MOCKCPP_GLOBAL_MOCK_OBJECT_H
#define __MOCKCPP_GLOBAL_MOCK_OBJECT_H

#include <mockcpp/mockcpp.h>

#if defined(MOCKCPP_USE_MOCKABLE) 
#  include <mockcpp/ChainableMockObject.h>
#else
#  include <mockcpp/HookMockObject.h>
#endif

MOCKCPP_NS_START

#if defined(MOCKCPP_USE_MOCKABLE) 
typedef ChainableMockObject MockObjectType;
#else
typedef HookMockObject MockObjectType;
#endif

struct GlobalMockObject
{
   static void verify();
   static void reset();

   static MockObjectType instance;
};

MOCKCPP_NS_END

#endif

