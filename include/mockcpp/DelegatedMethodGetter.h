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

#ifndef __MOCKCPP_DELEGATED_METHOD_GETTER_H
#define __MOCKCPP_DELEGATED_METHOD_GETTER_H

#include <mockcpp/mockcpp.h>

#include <mockcpp/MethodTypeTraits.h>
#include <mockcpp/DelegatedMethod.h>
#include <mockcpp/MethodInfoReader.h>

MOCKCPP_NS_START

#define DELEGATED_METHOD_GET(N, I) \
case I: \
{ \
    return getAddrOfMethod(&DelegatedMethod<N, I, ArgumentsList>::operator()); \
} \

void maxVtblSizeTooBigError(unsigned int index);

template <int VPTRIndex, typename ArgumentsList>
struct DelegatedMethodGetter
{
	static void* get(unsigned int index)
   {
		switch(index)
      {
#     include <mockcpp/DelegatedMethodGetDef.h>
      default: break;
      }

		maxVtblSizeTooBigError(index);

      return 0;
   }
};

////////////////////////////////////////////////
#define DELEGATED_METHOD_GET_BY_VPTR(N, I) \
case N: \
{ \
   return DelegatedMethodGetter<N, MethodArgumentsList>::get(I); \
}

void maxInheritanceTooBigError(unsigned int index);

template <typename C, typename Method>
void* getDelegatedFunction(unsigned int vptrIndex, unsigned int vtblIndex, Method m)
{
   typedef typename MethodTypeTraits<C, Method>::MethodArgumentsList MethodArgumentsList; 
   
   switch(vptrIndex)
   {
#     include <mockcpp/DelegatedMethodGetByVptrDef.h>
   default:
      break;
   }

	maxInheritanceTooBigError(vptrIndex);

   return 0;
}

MOCKCPP_NS_END

#endif

