/***
   emock is a cross-platform easy-to-use C++ Mock Framework based on mockcpp.
   Copyright [2017] [ez8.co] [orca <orca.zhang@yahoo.com>]

   This library is released under the Apache License, Version 2.0.
   Please see LICENSE file or visit https://github.com/ez8-co/emock for details.
   
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

#ifndef __EMOCK_CHAINABLE_MOCK_METHOD_CORE_H
#define __EMOCK_CHAINABLE_MOCK_METHOD_CORE_H

#include <emock/emock.h>

#include <emock/Method.h>
#include <emock/InvocationMockerContainer.h>

#include <string>

EMOCK_NS_START

struct Stub;
struct ChainableMockMethodCoreImpl;
struct SelfDescribe;
struct InvokedRecorder;
struct InvocationMockerNamespace;

struct ChainableMockMethodCore
      : public Method,
		  public InvocationMockerContainer
{
public:

    ChainableMockMethodCore(const std::string& name, 
                            InvocationMockerNamespace* ns);
    ~ChainableMockMethodCore();

    // Method
    const Any& 
        invoke( const std::string& nameOfCaller
              , const RefAny& p1 
              , const RefAny& p2
              , const RefAny& p3
              , const RefAny& p4
              , const RefAny& p5
              , const RefAny& p6
              , const RefAny& p7
              , const RefAny& p8
              , const RefAny& p9
              , const RefAny& p10
              , const RefAny& p11
              , const RefAny& p12
              , SelfDescribe* &resultProvider);

    std::string& getName(void) const;

    InvocationMockerNamespace* getNamespace() const;

public:

    // InvocationMockContainer
    InvocationMocker* getInvocationMocker(const std::string& id);
    void addInvocationMocker(InvocationMocker* mocker);
    void addDefaultInvocationMocker(InvocationMocker* mocker);

public:
    // Others
    void reset();
    void verify();

private:

    ChainableMockMethodCoreImpl* This;
};

EMOCK_NS_END

#endif

