
#ifndef __MOCKCPP_API_HOOK_HOLDER_FACTORY_H__
#define __MOCKCPP_API_HOOK_HOLDER_FACTORY_H__

#include <mockcpp/ParameterizedApiHookHolder.h>

MOCKCPP_NS_START

struct ApiHookHolder;

struct ApiHookHolderFactory
{
   template <typename F>
   static ApiHookHolder* create(F* api)
   {
      return new ParameterizedApiHookHolder<F>(api);
   }
};

MOCKCPP_NS_END

#endif

