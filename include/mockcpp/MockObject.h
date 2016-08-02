
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

