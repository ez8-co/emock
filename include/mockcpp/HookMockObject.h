
#ifndef __MOCKCPP_HOOK_MOCK_OBJECT_H__
#define __MOCKCPP_HOOK_MOCK_OBJECT_H__

#include <mockcpp/mockcpp.h>
#include <mockcpp/ChainableMockObjectBase.h>
#include <mockcpp/InvocationMockBuilderGetter.h>
#include <mockcpp/ChainableMockMethod.h>

MOCKCPP_NS_START

struct ApiHookHolder;
struct HookMockObjectImpl;

struct HookMockObject : public ChainableMockObjectBase
{
    HookMockObject(const std::string& name);
    ~HookMockObject();

    // Building-invocation-mocker interface -- Used in test case
    InvocationMockBuilderGetter method
               ( const std::string& name
               , const void* api
               , ApiHookHolder* holder);

    // Invoking interface --  Used in Functor
    template <typename RT>
    ChainableMockMethod<RT> invoke(const void* api) 
    {
      return ChainableMockMethod<RT>(getInvokable(api)); 
    }

    void reset();

private:

    // It's only for template-method invoke. we have to make it visible.
    Invokable* getInvokable(const void* api);

private:	
    HookMockObjectImpl* This;	
};

MOCKCPP_NS_END

#endif
