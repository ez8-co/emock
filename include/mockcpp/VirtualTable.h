
#ifndef __MOCKCPP_VIRTUAL_TABLE_H
#define __MOCKCPP_VIRTUAL_TABLE_H

#include <typeinfo>

#include <mockcpp/mockcpp.h>

MOCKCPP_NS_START

struct ObjectNameGetter;
struct IndexInvokableGetter;
struct VirtualTableImpl;

struct VirtualTable
{
   VirtualTable( IndexInvokableGetter* getter
               , ObjectNameGetter* nameGetter
               , unsigned int numberOfVptr
               , const std::type_info&);

   ~VirtualTable();

   void* toPointerToInterface() const;

   void addMethod(void* methodAddr, unsigned int indexOfVtbl, unsigned int indexofVptr = 0);
   void setDestructor(unsigned int vptrIndex, unsigned int vtblIndex);

   void expectsBeingDeleted();
   void expectsKeepAlive();

   void verify();
   void reset();

   static IndexInvokableGetter* getInvokableGetter(void* Caller, unsigned int indexOfVptr);

private:
	VirtualTableImpl* This;
};

MOCKCPP_NS_END

#endif

