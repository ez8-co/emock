/**
    TestNG++ is a practical, easy-to-use C/C++ xUnit framework.
    Copyright (C) <2009>  <Arthur Yuan: arthur.ii.yuan@gmail.com>

    TestNG++ is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    TestNG++ is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with TestNG++.  If not, see <http://www.gnu.org/licenses/>.
**/

#include <testngpp/testngpp.h>

#include <typeinfo>

#include <stdlib.h>

#if (__GNUC__ && __GNUC__ > 3) || (__MSC_VER && __MSC_VER > 1300)
#include <cxxabi.h>
#endif

#include <string>

TESTNGPP_NS_START

std::string getDemangledName(const std::type_info& typeInfo)
{
#if (__GNUC__ && __GNUC__ > 3) || (__MSC_VER && __MSC_VER > 1300 )
   int status;

   char* name = abi::__cxa_demangle( typeInfo.name(), 0, 0, & status);

   std::string result(name);

   ::free(name);
   
   return result;
#else
   return typeInfo.name();
#endif
}

TESTNGPP_NS_END

