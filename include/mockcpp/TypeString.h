
#ifndef __MOCKCPP_TYPE_STRING_H
#define __MOCKCPP_TYPE_STRING_H

#include <mockcpp/mockcpp.h>

#include <mockcpp/Void.h>

#include <string>
#include <typeinfo>

MOCKCPP_NS_START

std::string getDemangledName(const std::type_info& typeInfo);

template <typename T> struct TypeString
{
   static std::string value()
   {
       return getDemangledName(typeid(T));
   }
};

template <>
struct TypeString<std::string>
{
   static std::string value()
   {
      return "std::string";
   }
};

MOCKCPP_NS_END

#endif

