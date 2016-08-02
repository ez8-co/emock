
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

