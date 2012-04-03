
#ifndef __MOCKCPP_INTERFACE_INFO_H_
#define __MOCKCPP_INTERFACE_INFO_H_

#if defined(__GNUC__)
#include <typeinfo>
#endif

#include <mockcpp/mockcpp.h>

MOCKCPP_NS_START

#if defined(__GNUC__)

//////////////////////////////////////////////////////
unsigned int
getNumberOfBaseClasses(const std::type_info& info);

//////////////////////////////////////////////////////
template <typename Interface>
unsigned int getNumberOfVtbls()
{
   return getNumberOfBaseClasses(typeid(Interface));
}

#else

template <typename Interface>
unsigned int getNumberOfVtbls()
{
   return sizeof(Interface)/sizeof(void*);
}

#endif

MOCKCPP_NS_END

#endif

