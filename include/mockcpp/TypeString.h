/***
   mockcpp is a C/C++ mock framework.
   Copyright [2008] [Darwin Yuan <darwin.yuan@gmail.com>]

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
***/

#ifndef __MOCKCPP_TYPE_STRING_H
#define __MOCKCPP_TYPE_STRING_H

#include <mockcpp/mockcpp.h>

#include <mockcpp/Void.h>

#include <string>
#include <typeinfo>

MOCKCPP_NS_START

std::string getDemangledName(const char* info_name);

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

