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

#include <mockcpp/MockObjectBase.h>
#include <mockcpp/IndexInvokableGetter.h>
#include <mockcpp/Invokable.h>
#include <mockcpp/VirtualTable.h>
#include <mockcpp/ChainableMockMethodCore.h>
#include <mockcpp/ChainableMockMethodIndexKey.h>
#include <mockcpp/ChainableMockMethodContainer.h>
#include <mockcpp/InvocationMockBuilderGetter.h>

MOCKCPP_NS_START

struct MockObjectBaseImpl : public IndexInvokableGetter
{
   MockObjectBaseImpl( unsigned int numberOfVptr
                     , ChainableMockMethodContainer* c
                     , ObjectNameGetter* nameGetter
                     , const std::type_info& info);

   ~MockObjectBaseImpl();

   Invokable* getInvokable(unsigned int vptrIndex, unsigned int vtblIndex) const;

   ChainableMockMethodCore*
   getMethod(const std::string& name, void* addr, \
             unsigned int vptrIndex, unsigned int vtblIndex, \
             InvocationMockerNamespace* ns);

   VirtualTable* vtbl;
   ChainableMockMethodContainer* container;

   void reset();

private:

   ChainableMockMethodCore*
   createMethod(const std::string& name, void* addr, \
       unsigned int vptrIndex, unsigned int vtblIndex, \
       InvocationMockerNamespace* ns);
};

////////////////////////////////////////////////////////////////////////
MockObjectBaseImpl::
MockObjectBaseImpl( unsigned int numberOfVptr
                  , ChainableMockMethodContainer* c
                  , ObjectNameGetter* nameGetter
                  , const std::type_info& info)
    : container(c)
{
	vtbl = new VirtualTable(this, nameGetter, numberOfVptr, info);
}

////////////////////////////////////////////////////////////////////////
MockObjectBaseImpl::~MockObjectBaseImpl()
{
   delete vtbl;
}

////////////////////////////////////////////////////////////////////////
void MockObjectBaseImpl::reset()
{
    vtbl->reset();
    container->reset();
}

////////////////////////////////////////////////////////////////////////
Invokable*
MockObjectBaseImpl::
getInvokable(unsigned int vptrIndex, unsigned int vtblIndex) const
{
    ChainableMockMethodIndexKey key(vptrIndex, vtblIndex);

    return container->getMethod(&key);
}

////////////////////////////////////////////////////////////////////////
ChainableMockMethodCore*
MockObjectBaseImpl::
createMethod(const std::string& name, void* addr, \
       unsigned int vptrIndex, unsigned int vtblIndex, \
       InvocationMockerNamespace* ns)
{
    ChainableMockMethodIndexKey* key = \
             new ChainableMockMethodIndexKey(vptrIndex, vtblIndex);
    ChainableMockMethodCore* method = \
             new ChainableMockMethodCore(name, ns);
    
    container->addMethod(key, method);

    vtbl->addMethod(addr, vtblIndex, vptrIndex);
  
    return method;
}
////////////////////////////////////////////////////////////////////////
ChainableMockMethodCore*
MockObjectBaseImpl::getMethod(const std::string& name, void* addr, \
       unsigned int vptrIndex, unsigned int vtblIndex, \
       InvocationMockerNamespace* ns)
{
    ChainableMockMethodIndexKey key(vptrIndex, vtblIndex);
    ChainableMockMethodCore* method = container->getMethod(&key);
    if(method != 0)
    {
       return method;
    }

    return createMethod(name, addr, vptrIndex, vtblIndex, ns);
}

////////////////////////////////////////////////////////////////////////
MockObjectBase::MockObjectBase( const std::string& objName
                              , unsigned int numberOfVptr
                              , const std::type_info& info)
   : ChainableMockObjectBase(objName)
{
	This = new MockObjectBaseImpl(numberOfVptr
               , this->getMethodContainer()
               , this
               , info);
}

////////////////////////////////////////////////////////////////////////
MockObjectBase::MockObjectBase( const MockObjectBase& obj)
   : ChainableMockObjectBase(obj)
   , This(obj.This)
{
}

////////////////////////////////////////////////////////////////////////
MockObjectBase::~MockObjectBase()
{
   if(!shared)
   {
      delete This;
   }
}

////////////////////////////////////////////////////////////////////////
InvocationMockBuilderGetter
MockObjectBase::
createInvocationMockerBuilderGetter(const std::string& name, \
          void* addr, unsigned int vptrIndex, unsigned int vtblIndex)
{
   ChainableMockMethodCore* method = \
          This->getMethod(name, addr, vptrIndex, vtblIndex, this);

   return InvocationMockBuilderGetter(method, method);
}

////////////////////////////////////////////////////////////////////////
void*
MockObjectBase::toPointerToInterface() const
{
   return This->vtbl->toPointerToInterface();
}

////////////////////////////////////////////////////////////////////////
void MockObjectBase::
setDestructor(unsigned int vptrIndex, unsigned int vtblIndex)
{
   This->vtbl->setDestructor(vptrIndex, vtblIndex);
}

////////////////////////////////////////////////////////////////////////
void MockObjectBase::expectsBeingDeleted()
{
   This->vtbl->expectsBeingDeleted();
}

////////////////////////////////////////////////////////////////////////
void MockObjectBase::expectsKeepAlive()
{
   This->vtbl->expectsKeepAlive();
}

////////////////////////////////////////////////////////////////////////
void
MockObjectBase::reset()
{
   This->reset();
}

////////////////////////////////////////////////////////////////////////
void
MockObjectBase::verify()
{
   ChainableMockObjectBase::verify();
   This->vtbl->verify();
}

////////////////////////////////////////////////////////////////////////

MOCKCPP_NS_END

