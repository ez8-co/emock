#ifndef __MOCKCPP_GNU_METHOD_INDICES_CHECKER_H
#define __MOCKCPP_GNU_METHOD_INDICES_CHECKER_H

#include <algorithm>
#include <mockcpp/mockcpp.h>
#include <mockcpp/GnuMethodInfoReader.h>

MOCKCPP_NS_START

template <typename Interface, typename Method>
std::pair<unsigned int, unsigned int>
getIndicesOfMethod(Method m)
{
   unsigned int vptrIndex = getDeltaOfMethod<Interface, Method>(m);
   unsigned int vtblIndex = getIndexOfMethod<Interface, Method>(m);
   return std::pair<unsigned int, unsigned int>
       (vptrIndex, vtblIndex);
}

MOCKCPP_NS_END

#endif

