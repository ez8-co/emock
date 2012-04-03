/***
    mockcpp is a generic C/C++ mock framework.
    Copyright (C) <2009>  <Darwin Yuan: darwin.yuan@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
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

