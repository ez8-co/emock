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

#include <mockcpp/mockcpp.h>

#include <typeinfo>

#include <stdlib.h>

#if defined(__GNUC__)
#include <cxxabi.h>
#endif

#include <string>

MOCKCPP_NS_START

MOCKCPP_EXPORT

std::string getDemangledName(const char* info_name)
{
#if defined(__GNUC__)

   int status;
   char* name = abi::__cxa_demangle(info_name, 0, 0, & status);
   std::string result(name ? name : info_name);
   free(name);
   return result;

#else

   return info_name;

#endif
}

std::string getDemangledName(const std::type_info& typeInfo)
{
   return getDemangledName(typeInfo.name());
}

MOCKCPP_NS_END

