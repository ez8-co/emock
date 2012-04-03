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

#ifndef __MOCKCPP_METHOD_TYPE_TRAITS_H
#define __MOCKCPP_METHOD_TYPE_TRAITS_H

#include <mockcpp/mockcpp.h>

#include <mockcpp/ArgumentsList.h>
#include <mockcpp/ArgumentsMacroHelpers.h>

MOCKCPP_NS_START

template <typename C, typename Method>
struct MethodTypeTraits;

#define MOCKCPP_METHOD_TYPE_TRAITS_DEF(n) \
template <typename C, typename C1, typename R DECL_TEMPLATE_ARGS(n)> \
struct MethodTypeTraits<C, R (C1::*) (DECL_ARGS(n))> \
{ \
   typedef C1 OrignalClass; \
   typedef R (C::*MethodType)(DECL_ARGS(n)); \
 \
   typedef ArgumentsList<R DECL_REST_ARGS(n)> MethodArgumentsList; \
}

#define MOCKCPP_CONST_METHOD_TYPE_TRAITS_DEF(n) \
template <typename C, typename C1, typename R DECL_TEMPLATE_ARGS(n)> \
struct MethodTypeTraits<C, R (C1::*) (DECL_ARGS(n)) const> \
{ \
   typedef C1 OrignalClass; \
   typedef R (C::*MethodType)(DECL_ARGS(n)) const; \
 \
   typedef ArgumentsListConst<R DECL_REST_ARGS(n)> MethodArgumentsList; \
}

#include <mockcpp/MethodTypeTraitsDef.h>

MOCKCPP_NS_END

#endif
