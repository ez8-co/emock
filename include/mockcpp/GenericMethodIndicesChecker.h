
#include <algorithm>
#include <typeinfo>

#include <mockcpp/mockcpp.h>
#include <mockcpp/MethodTypeTraits.h>
#include <mockcpp/MethodIndiceChecker.h>

MOCKCPP_NS_START

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////
template <typename Interface, typename Method>
std::pair<unsigned int, unsigned int>
getIndicesOfMethod(Method m)
{
   typedef typename MethodTypeTraits<Interface, Method>::MethodType ExpectedMethodType;
   ExpectedMethodType expectedMethod = m;

   typedef void (Interface::*Checker)(void*);

   Checker check = \
      reinterpret_cast<Checker>(expectedMethod);

   MethodIndiceChecker* checker = createMethodIndiceChecker(typeid(Interface));

   Interface* iface = (Interface*)checker->getObject();

   (iface->*check)(0);
   
   unsigned int vptrIndex = 0;
   unsigned int vtblIndex = 0;

   bool result = checker->getIndice(false, vptrIndex, vtblIndex);

   delete checker;

   MOCKCPP_ASSERT_TRUE("You are trying to mock a non-pure-virtual object", result); 

   return std::pair<unsigned int, unsigned int>
       (vptrIndex, vtblIndex);
};


///////////////////////////////////////////////////////////////////////

MOCKCPP_NS_END

