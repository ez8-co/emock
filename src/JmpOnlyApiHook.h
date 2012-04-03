
#ifndef __MOCKCPP_JMP_ONLY_API_HOOK_H__
#define __MOCKCPP_JMP_ONLY_API_HOOK_H__

#include <mockcpp/mockcpp.h>

MOCKCPP_NS_START

struct JmpOnlyApiHookImpl;

struct JmpOnlyApiHook
{
    JmpOnlyApiHook
       ( const void* api
       , const void* stub );

    ~JmpOnlyApiHook();

private:
    JmpOnlyApiHookImpl* This;;
};

MOCKCPP_NS_END

#endif
