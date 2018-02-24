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

#include <emock/emock.h>

#include <emock/HookMockObject.h>
#include <emock/ChainableMockMethodCore.h>
#include <emock/InvocationMockBuilderGetter.h>
#include <emock/InvocationMockerNamespace.h>
#include <emock/ApiHookKey.h>
#include <emock/ReportFailure.h>
#include <emock/ApiHookHolder.h>
#include <emock/SymbolRetriever.h>
#include "Trampoline.h"

EMOCK_NS_START

//////////////////////////////////////////////////////////////
struct HookMockObjectImpl
{
   HookMockObjectImpl(ChainableMockMethodContainer* c)
      : container(c)
   {}

   ChainableMockMethodCore*
   getMethod( const std::string& name
            , const void* api
            , ApiHookHolder* hookHolder
            , InvocationMockerNamespace* ns
            , bool isMemFun);
   
   ChainableMockMethodCore*
   getMethod(const void* api);
   
   void reset();

   ChainableMockMethodContainer* container;

private:

   ChainableMockMethodCore* 
   addMethod( const std::string& name
            , const void* api
	    , ApiHookHolder* hookHolder
	    , InvocationMockerNamespace* ns
      , bool isMemFun); 

};

//////////////////////////////////////////////////////////////
void
HookMockObjectImpl::reset()
{
    container->reset();
    SymbolRetriever::reset();
    Trampoline::reset();
}

//////////////////////////////////////////////////////////////
ChainableMockMethodCore*
HookMockObjectImpl::
addMethod( const std::string& name
         , const void* api
         , ApiHookHolder* hookHolder
         , InvocationMockerNamespace* ns
         , bool isMemFun)
{
    ApiHookKey* key = new ApiHookKey(api, hookHolder, isMemFun);
    ChainableMockMethodCore* method = new ChainableMockMethodCore(name, ns);

    container->addMethod(key, method);

    return method;
}
//////////////////////////////////////////////////////////////
ChainableMockMethodCore*
HookMockObjectImpl::
getMethod(const std::string& name, const void* api
         , ApiHookHolder* hookHolder
         , InvocationMockerNamespace* ns
         , bool isMemFun)
{
    ChainableMockMethodCore* method = getMethod(api);
    if (method != 0)
    {
      delete hookHolder;
      return method;
    }

    return addMethod(name, api, hookHolder, ns, isMemFun);
}

//////////////////////////////////////////////////////////////
ChainableMockMethodCore*
HookMockObjectImpl::
getMethod(const void* api) 
{
    ApiHookKey key(api);
    return container->getMethod(&key);
}

//////////////////////////////////////////////////////////////
HookMockObject::HookMockObject(const std::string& name)
   : ChainableMockObjectBase(name)
{
   This = new HookMockObjectImpl(this->getMethodContainer());
}

//////////////////////////////////////////////////////////////
HookMockObject::~HookMockObject()
{
   delete This;
}

//////////////////////////////////////////////////////////////
InvocationMockBuilderGetter
HookMockObject::method(const std::string& name, const void* api, ApiHookHolder* hookHolder, bool isMemFun)
{
    ChainableMockMethodCore* core = This->getMethod(name, api, hookHolder, this, isMemFun);
    return InvocationMockBuilderGetter(core, core);
}

//////////////////////////////////////////////////////////////
// Private
Invokable*
HookMockObject::getInvokable(const void* api) 
{
   ChainableMockMethodCore* method = This->getMethod(api);
   EMOCK_ASSERT_TRUE(
	   "mockcpp internal error (3001): unable to get api pointer",
	   method != 0);
   return method;
}

//////////////////////////////////////////////////////////////
void HookMockObject::reset()
{
   This->reset();
}

//////////////////////////////////////////////////////////////

EMOCK_NS_END


