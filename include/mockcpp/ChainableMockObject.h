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

#ifndef __MOCKCPP_CHAINABLE_MOCK_OBJECT_H_
#define __MOCKCPP_CHAINABLE_MOCK_OBJECT_H_

#include <mockcpp/mockcpp.h>

#include <mockcpp/ChainableMockObjectBase.h>
#include <mockcpp/ChainableMockMethod.h>
#include <mockcpp/InvocationMockBuilderGetter.h>

#include <string>

MOCKCPP_NS_START

struct ChainableMockObjectImpl;
struct Invokable;

struct ChainableMockObject 
      : public ChainableMockObjectBase
{
public:

    ChainableMockObject(const std::string& name);

    ~ChainableMockObject();

    // Building-invocation-mocker interface -- Used in test case
    InvocationMockBuilderGetter method(const std::string& name);

    // Invoking interface --  Used in Functor
    template <typename RT>
    ChainableMockMethod<RT> invoke(const std::string& name) 
    {
      return ChainableMockMethod<RT>(getInvokable(name)); 
    }

    void reset();

public:

    // It's only for template-method invoke. we have to make it visible.
    Invokable* getInvokable(const std::string& name); 

private:

    ChainableMockObjectImpl* This;
};

MOCKCPP_NS_END

#endif

