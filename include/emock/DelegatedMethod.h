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

#ifndef __EMOCK_DELEGATED_METHOD_H
#define __EMOCK_DELEGATED_METHOD_H

#include <emock/emock.h>

#include <emock/ArgumentsList.h>
#include <emock/VirtualTable.h>
#include <emock/ChainableMockMethod.h>
#include <emock/ArgumentsMacroHelpers.h>
#include <emock/IndexInvokableGetter.h>

EMOCK_NS_START

/////////////////////////////////////////////////////////////////
template <int VPTRIndex, int VTBLIndex, typename ArgumentsList>
struct DelegatedMethod;

/////////////////////////////////////////////////////////////////
#define EMOCK_DELEGATED_METHOD_DEF(n) \
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
#define EMOCK_CONST_DELEGATED_METHOD_DEF(n) \
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
#include <emock/DelegatedMethodDef.h>

EMOCK_NS_END

#endif

