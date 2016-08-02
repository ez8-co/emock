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

#include <mockcpp/mockcpp.h>

#include <mockcpp/ChainableMockObject.h>
#include <mockcpp/ChainableMockMethodCore.h>
#include <mockcpp/InvocationMockBuilderGetter.h>
#include <mockcpp/ChainableMockMethodNameKey.h>
#include <mockcpp/InvocationMockerNamespace.h>

MOCKCPP_NS_START

//////////////////////////////////////////////////////////////
struct ChainableMockObjectImpl
{
   ChainableMockObjectImpl(ChainableMockMethodContainer* c)
      : container(c)
   {}

   ChainableMockMethodCore*
   getMethod(const std::string& name, InvocationMockerNamespace* ns);
   
   void reset();

   ChainableMockMethodContainer* container;

private:

   ChainableMockMethodCore* 
   addMethod(const std::string& name, InvocationMockerNamespace* ns); 

};

//////////////////////////////////////////////////////////////
void
ChainableMockObjectImpl::reset()
{
    container->reset();
}

//////////////////////////////////////////////////////////////
ChainableMockMethodCore*
ChainableMockObjectImpl::
addMethod(const std::string& name, InvocationMockerNamespace* ns) 
{
    ChainableMockMethodNameKey* key = new ChainableMockMethodNameKey(name);
    ChainableMockMethodCore* method = new ChainableMockMethodCore(name, ns);

    container->addMethod(key, method);

    return method;
}
//////////////////////////////////////////////////////////////
ChainableMockMethodCore*
ChainableMockObjectImpl::
getMethod(const std::string& name, InvocationMockerNamespace* ns) 
{
    ChainableMockMethodNameKey key(name);

    ChainableMockMethodCore* method = container->getMethod(&key);
    if (method != 0)
    {
      return method;
    }

    return addMethod(name, ns);
}

//////////////////////////////////////////////////////////////
ChainableMockObject::ChainableMockObject(const std::string& name)
    : ChainableMockObjectBase(name)
{
	This = new ChainableMockObjectImpl(this->getMethodContainer());
}

//////////////////////////////////////////////////////////////
ChainableMockObject::~ChainableMockObject()
{
   delete This;
}

//////////////////////////////////////////////////////////////
InvocationMockBuilderGetter
ChainableMockObject::method(const std::string& name)
{
    ChainableMockMethodCore* core = This->getMethod(name, this);
    return InvocationMockBuilderGetter(core, core);
}

//////////////////////////////////////////////////////////////
// Private
Invokable*
ChainableMockObject::getInvokable(const std::string& name) 
{
   return This->getMethod(name, this);
}

//////////////////////////////////////////////////////////////
void ChainableMockObject::reset()
{
   This->reset();
}

//////////////////////////////////////////////////////////////

MOCKCPP_NS_END


