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

#ifndef __MOCKCPP_DELEGATED_METHOD_H
#define __MOCKCPP_DELEGATED_METHOD_H

#include <mockcpp/mockcpp.h>

#include <mockcpp/ArgumentsList.h>
#include <mockcpp/VirtualTable.h>
#include <mockcpp/ChainableMockMethod.h>
#include <mockcpp/ArgumentsMacroHelpers.h>
#include <mockcpp/IndexInvokableGetter.h>

MOCKCPP_NS_START

/////////////////////////////////////////////////////////////////
template <int VPTRIndex, int VTBLIndex, typename ArgumentsList>
struct DelegatedMethod;

/////////////////////////////////////////////////////////////////
#define MOCKCPP_DELEGATED_METHOD_DEF(n) \
template <int VPTRIndex, int VTBLIndex, typename R DECL_TEMPLATE_ARGS(n)> \
struct DelegatedMethod<VPTRIndex, VTBLIndex, ArgumentsList<R DECL_REST_ARGS(n)> > \
{ \
   enum { IsConst = 0 }; \
   enum { NumberOfParameters = n }; \
  \
	R operator()(DECL_PARAMS_LIST(n)) \
   { \
      IndexInvokableGetter* getter = \
                      VirtualTable::getInvokableGetter(this, VPTRIndex); \
      return ChainableMockMethod<R>(getter->getInvokable(VPTRIndex, VTBLIndex)) \
                      ("" DECL_REST_PARAMS(n)); \
   } \
}

/////////////////////////////////////////////////////////////////
#define MOCKCPP_CONST_DELEGATED_METHOD_DEF(n) \
template <int VPTRIndex, int VTBLIndex, typename R DECL_TEMPLATE_ARGS(n)> \
struct DelegatedMethod<VPTRIndex, VTBLIndex, ArgumentsListConst<R DECL_REST_ARGS(n)> > \
{ \
   enum { IsConst = 1 }; \
   enum { NumberOfParameters = n }; \
  \
	R operator()(DECL_PARAMS_LIST(n)) \
   { \
      IndexInvokableGetter* getter = \
                      VirtualTable::getInvokableGetter(this, VPTRIndex); \
      return ChainableMockMethod<R>(getter->getInvokable(VPTRIndex, VTBLIndex)) \
                      ("" DECL_REST_PARAMS(n)); \
   } \
}

/////////////////////////////////////////////////////////////////
#include <mockcpp/DelegatedMethodDef.h>

MOCKCPP_NS_END

#endif

