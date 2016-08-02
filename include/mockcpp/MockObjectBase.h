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

#ifndef __MOCKCPP_MOCK_OBJECT_BASE_H
#define __MOCKCPP_MOCK_OBJECT_BASE_H

#include <typeinfo>

#include <mockcpp/mockcpp.h>
#include <mockcpp/ChainableMockObjectBase.h>
#include <mockcpp/InvocationMockBuilderGetter.h>

MOCKCPP_NS_START

struct MockObjectBaseImpl;

struct MockObjectBase : public ChainableMockObjectBase
{
   ~MockObjectBase();

   virtual void reset();
   virtual void verify();

protected:

   MockObjectBase( const std::string& objName
                 , unsigned int numberOfVptr
                 , const std::type_info& info);

   MockObjectBase(const MockObjectBase&);

protected:

   InvocationMockBuilderGetter
   createInvocationMockerBuilderGetter(const std::string& name, \
          void* addr, unsigned int vptrIndex, unsigned int vtblIndex);
   
   void* toPointerToInterface() const;

   void setDestructor(unsigned int vptrIndex, unsigned int vtblIndex);

   void expectsBeingDeleted();
   void expectsKeepAlive();

private:

   MockObjectBase& operator=(const MockObjectBase&);

private:

   MockObjectBaseImpl* This;
};

MOCKCPP_NS_END

#endif

