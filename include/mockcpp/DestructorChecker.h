
#ifndef __MOCKCPP_DESTRUCTOR_CHECKER_H
#define __MOCKCPP_DESTRUCTOR_CHECKER_H

#include <algorithm>
#include <typeinfo>

#include <mockcpp/mockcpp.h>
#include <mockcpp/MethodIndiceChecker.h>
#include <mockcpp/ReportFailure.h>

MOCKCPP_NS_START

///////////////////////////////////////////////
template <typename Interface, typename Original>
std::pair<unsigned int, unsigned int> getIndexOfDestructor()
{
   MethodIndiceChecker* checker = createMethodIndiceChecker(typeid(Original));

   Interface* iface = (Original*) checker->getObject();

   delete iface;

   unsigned int vptrIndex = 0;
   unsigned int vtblIndex = 0;

   bool result = checker->getIndice(true, vptrIndex, vtblIndex);
   delete checker;

   MOCKCPP_ASSERT_TRUE("You are trying to mock an interface without virtual destructor", result); 

   return std::pair<unsigned int, unsigned int>
       (vptrIndex, vtblIndex);
};

///////////////////////////////////////////////

MOCKCPP_NS_END

#endif

