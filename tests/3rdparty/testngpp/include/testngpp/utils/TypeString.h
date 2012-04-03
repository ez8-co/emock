#ifndef __TESTNGPP_TYPE_STRING_H
#define __TESTNGPP_TYPE_STRING_H

#include <testngpp/testngpp.h>

#include <string>
#include <typeinfo>

TESTNGPP_NS_START

/////////////////////////////////////////////////////////
std::string getDemangledName(const std::type_info& typeInfo);

/////////////////////////////////////////////////////////
template <typename T> struct TypeString
{
	static std::string value()
	{
       return TESTNGPP_NS::getDemangledName(typeid(T));
   }
};

/////////////////////////////////////////////////////////
template <>
struct TypeString<std::string>
{
	static std::string value()
	{
      return "std::string";
   }
};

/////////////////////////////////////////////////////////

TESTNGPP_NS_END

#endif

