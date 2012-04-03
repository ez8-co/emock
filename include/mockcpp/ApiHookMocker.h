
#ifndef __MOCKCPP_API_HOOK_MOCKER_H__
#define __MOCKCPP_API_HOOK_MOCKER_H__

#include <mockcpp/mockcpp.h>
#include <mockcpp/GlobalMockObject.h>
#include <mockcpp/ApiHookHolderFactory.h>

MOCKCPP_NS_START

template <typename API>
InvocationMockBuilderGetter mockAPI(const std::string& name, API* api)
{
    return MOCKCPP_NS::GlobalMockObject::instance.method
                 ( name
                 , reinterpret_cast<const void*>(api)
                 , ApiHookHolderFactory::create(api));
}


MOCKCPP_NS_END

#endif

