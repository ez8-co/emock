
#ifndef __MOCKCPP_API_HOOK_HOLDER_H__
#define __MOCKCPP_API_HOOK_HOLDER_H__

#include <mockcpp/mockcpp.h>

MOCKCPP_NS_START

struct ApiHookHolder
{
   virtual void * getApiHook() const = 0;

   virtual ~ApiHookHolder() {}
};

MOCKCPP_NS_END

#endif

