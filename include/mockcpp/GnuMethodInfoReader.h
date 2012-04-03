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
#ifndef __MOCKCPP_GNU_METHOD_INFO_READER_H
#define __MOCKCPP_GNU_METHOD_INFO_READER_H

#include <algorithm>
#include <mockcpp/mockcpp.h>

#include <mockcpp/OutputStringStream.h>
#include <mockcpp/MethodTypeTraits.h>
#include <mockcpp/ReportFailure.h>
#include <mockcpp/TypeString.h>

MOCKCPP_NS_START

///////////////////////////////////////////////////////////
struct GnuMethodDescription
{
   union {
	  void* addr;
     int index;
   }u;
 
   int delta;
};

///////////////////////////////////////////////////////////
template <typename Method>
union MethodDescriptionUnion
{
    GnuMethodDescription desc;
    Method method;
};

///////////////////////////////////////////////////////////
template <typename Method>
void* getAddrOfMethod(Method input)
{
	MethodDescriptionUnion<Method> m;
	m.method = input;

   oss_t oss;
   oss << "Method address should be even, please make sure the method "
       << TypeString<Method>::value() << " is NOT a virtual method";
 
	MOCKCPP_ASSERT_TRUE(
		oss.str(),
	   !(m.desc.u.index%2));


   return m.desc.u.addr;
}

///////////////////////////////////////////////////////////
template <typename C, typename Method>
GnuMethodDescription getGnuDescOfVirtualMethod(Method input)
{
   typedef typename MethodTypeTraits<C, Method>::MethodType ExpectedMethodType; 
	MethodDescriptionUnion<ExpectedMethodType> m;
	m.method = input;

   oss_t oss;
   oss << "Virtual method address should be odd, please make sure the method "
       << TypeString<Method>::value() << " is a virtual method";
 
	MOCKCPP_ASSERT_TRUE(
		oss.str(),
	   (m.desc.u.index%2));

	return m.desc;
}

///////////////////////////////////////////////////////////
template <typename C, typename Method>
unsigned int getIndexOfMethod(Method method)
{
   return (getGnuDescOfVirtualMethod<C, Method>(method).u.index - 1)/sizeof(void*);
}

///////////////////////////////////////////////////////////
template <typename C, typename Method>
unsigned int getDeltaOfMethod(Method method)
{
   return getGnuDescOfVirtualMethod<C, Method>(method).delta/sizeof(void*);
}

MOCKCPP_NS_END

#endif

