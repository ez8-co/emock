
#ifndef __MOCKCPP_METHOD_INDICE_CHECKER_H
#define __MOCKCPP_METHOD_INDICE_CHECKER_H

#include <typeinfo>

#include <mockcpp/mockcpp.h>

MOCKCPP_NS_START

///////////////////////////////////////////////
struct MethodIndiceChecker
{
   virtual void* getObject() const = 0;

   virtual bool getIndice
      ( bool objDeleted
      , unsigned int& vptrIndex
      , unsigned int& vtblIndex) = 0;

   virtual ~MethodIndiceChecker() {}
};

///////////////////////////////////////////////
MethodIndiceChecker*
createMethodIndiceChecker(const std::type_info& info);

MOCKCPP_NS_END

#endif

