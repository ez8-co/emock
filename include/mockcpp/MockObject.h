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

#ifndef __MOCKCPP_MOCK_OBJECT_H
#define __MOCKCPP_MOCK_OBJECT_H

#include <algorithm>

#include <mockcpp/mockcpp.h>
#include <mockcpp/TypeString.h>
#include <mockcpp/MockObjectBase.h>
#include <mockcpp/DelegatedMethodGetter.h>
#include <mockcpp/InterfaceInfo.h>
#include <mockcpp/DestructorChecker.h>
#include <mockcpp/OutputStringStream.h>
#include <mockcpp/Asserter.h>
#include <mockcpp/ReportFailure.h>
#include <mockcpp/utils.h>

MOCKCPP_NS_START

////////////////////////////////////////////////////////////////
template <typename Interface>
struct MockObject : public MockObjectBase
{
   typedef Interface MockedInterface;

   /////////////////////////////////////////////////////////////
	MockObject()
		: MockObjectBase(TypeString<Interface>::value()
      , getNumberOfVtbls<Interface>()
      , typeid(Interface))
	{
      identifyDestructor<Interface, Interface>();
   }

   /////////////////////////////////////////////////////////////
   MockObject(const MockObject& obj)
     : MockObjectBase(obj)
   {
   }

   /////////////////////////////////////////////////////////////
   operator Interface* ()
   {
      return (Interface*)toPointerToInterface();
   }

   /////////////////////////////////////////////////////////////
   Interface* operator->()
   {
      return (Interface*)toPointerToInterface();
   }

   /////////////////////////////////////////////////////////////
   template <typename TargetInterface>
   void mightBeUsedAs()
   {
      TargetInterface* target = \
         dynamic_cast<TargetInterface*>
             ((Interface*)toPointerToInterface());
      if(target == 0)
      {
         oss_t oss;
         oss << TypeString<Interface>::value()
             << " can not be used as "
             << TypeString<TargetInterface>::value()
             << ".";

         MOCKCPP_REPORT_FAILURE(oss.str());
      }

      identifyDestructor<TargetInterface, Interface>();
   }

   /////////////////////////////////////////////////////////////
   void willBeDeleted()
   {
      expectsBeingDeleted();
   }

   /////////////////////////////////////////////////////////////
   void willKeepAlive()
   {
      expectsKeepAlive();
   }
   
   void verify()
   {   
      try
      {
         MockObjectBase::verify();
      }
      catch(...)
      {
          __RUN_NOTHROW({
              reset();
          });
          throw;
      }
   
      __RUN_THROW({
          reset();
      });      
   }

   void reset()
   {
      MockObjectBase::reset();
      identifyDestructor<Interface, Interface>();
   }
   /////////////////////////////////////////////////////////////
   template <typename Method>
   InvocationMockBuilderGetter method_helper(Method m, const char* method_prefix, const char* method_suffix)
   {
     std::string method_name(method_prefix);
     method_name += TypeString<MockedInterface>::value();
     method_name += "::";
     method_name += method_suffix;
     return method(m, method_name.c_str());
  }

	template <typename Method>
   InvocationMockBuilderGetter method(Method m, const char* name = 0)
   {
     std::string methodName(name == 0 ? \
         TypeString<Method>::value():name);

     std::pair<unsigned int, unsigned int> indices = \
         getIndicesOfMethod<Interface, Method>(m);

     void * addr = getDelegatedFunction<Interface, Method>( \
         indices.first, indices.second, m);

     return createInvocationMockerBuilderGetter( \
               methodName, addr, indices.first, indices.second);
	}

////////////////////////////////////////////////////////////////
private:

   MockObject& operator=(const MockObject&);

////////////////////////////////////////////////////////////////
// Template methods: it's ugly, but we have to make them visible.
private:

   template <typename T, typename Original>
   void identifyDestructor()
   {
      std::pair<unsigned int, unsigned int> indices = \
         getIndexOfDestructor<T, Original>();

      setDestructor(indices.first, indices.second);
   }

   template <typename Method>
   void* getAddrOfDelegatedMethod(Method m)
   { return getAddrOfMethod(m); }

};

MOCKCPP_NS_END

#endif

