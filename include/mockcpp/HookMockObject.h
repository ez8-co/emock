/***
   mockcpp is a C/C++ mock framework.
   Copyright [2008] [Darwin Yuan <darwin.yuan@gmail.com>]

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
***/

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

public:

    // It's only for template-method invoke. we have to make it visible.
    Invokable* getInvokable(const void* api);

private:	
    HookMockObjectImpl* This;	
};

MOCKCPP_NS_END

#endif
