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

