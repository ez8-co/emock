
#ifndef __MOCKCPP_DELEGATED_METHOD_GETTER_H
#define __MOCKCPP_DELEGATED_METHOD_GETTER_H

#include <mockcpp/mockcpp.h>

#include <mockcpp/MethodTypeTraits.h>
#include <mockcpp/DelegatedMethod.h>
#include <mockcpp/MethodInfoReader.h>

MOCKCPP_NS_START

#define DELEGATED_METHOD_GET(N, I) \
case I: \
{ \
    return getAddrOfMethod(&DelegatedMethod<N, I, ArgumentsList>::operator()); \
} \

void maxVtblSizeTooBigError(unsigned int index);

template <int VPTRIndex, typename ArgumentsList>
struct DelegatedMethodGetter
{
	static void* get(unsigned int index)
   {
		switch(index)
      {
#     include <mockcpp/DelegatedMethodGetDef.h>
      default: break;
      }

		maxVtblSizeTooBigError(index);

      return 0;
   }
};

////////////////////////////////////////////////
#define DELEGATED_METHOD_GET_BY_VPTR(N, I) \
case N: \
{ \
   return DelegatedMethodGetter<N, MethodArgumentsList>::get(I); \
}

void maxInheritanceTooBigError(unsigned int index);

template <typename C, typename Method>
void* getDelegatedFunction(unsigned int vptrIndex, unsigned int vtblIndex, Method m)
{
   typedef typename MethodTypeTraits<C, Method>::MethodArgumentsList MethodArgumentsList; 
   
   switch(vptrIndex)
   {
#     include <mockcpp/DelegatedMethodGetByVptrDef.h>
   default:
      break;
   }

	maxInheritanceTooBigError(vptrIndex);

   return 0;
}

MOCKCPP_NS_END

#endif

