
#include <mockcpp/mockcpp.h>

#include <typeinfo>

#include <stdlib.h>

#if defined(__GNUC__)
#include <cxxabi.h>
#endif

#include <string>

MOCKCPP_NS_START

MOCKCPP_EXPORT
std::string getDemangledName(const std::type_info& typeInfo)
{
#if defined(__GNUC__)
   int status;

   char* name = abi::__cxa_demangle( typeInfo.name(), 0, 0, & status);

   std::string result(name);

   ::free(name);
   
   return result;

#else

   return typeInfo.name();

#endif
}

MOCKCPP_NS_END

