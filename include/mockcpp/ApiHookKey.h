
#ifndef __MOCKCPP_API_HOOK_KEY_H__
#define __MOCKCPP_API_HOOK_KEY_H__

#include <mockcpp/mockcpp.h>

#include <mockcpp/ChainableMockMethodKey.h>

MOCKCPP_NS_START

struct ApiHook;
struct ApiHookHolder;

struct ApiHookKey
    : public ChainableMockMethodKey
{
   explicit ApiHookKey(const void* api);
   ApiHookKey(const void* api, ApiHookHolder* hookHolder);

   ~ApiHookKey();
   
   bool equals(const ChainableMockMethodKey * const rhs) const;

private:
   ApiHook* hook;
   ApiHookHolder* hookHolder;
   const void* apiAddress;
};

MOCKCPP_NS_END

#endif

