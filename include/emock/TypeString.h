/***
   emock is a cross-platform easy-to-use C++ Mock Framework based on mockcpp.
   Copyright [2017] [ez8.co] [orca <orca.zhang@yahoo.com>]

   This library is released under the Apache License, Version 2.0.
   Please see LICENSE file or visit https://github.com/ez8-co/emock for details.
   
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

#ifndef __EMOCK_TYPE_STRING_H
#define __EMOCK_TYPE_STRING_H

#include <emock/emock.h>

#include <emock/Void.h>

#include <string>
#include <typeinfo>

EMOCK_NS_START

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

EMOCK_NS_END

#endif

