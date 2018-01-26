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

#ifndef __EMOCK_MOCKABLE_H
#define __EMOCK_MOCKABLE_H

#if defined(__cplusplus) && defined(EMOCK_USE_MOCKABLE)
#  include <emock/Functor.h>
#  define MOCKABLE(function) MOCKER(function).defaults().will(invoke(function)); \
                             PlaceHolder* function##_holder = MockableHelper(function); \
                             EMOCK_NS::Functor function(function##_holder, #function, __FUNCTION__)
#  define MCALL(function) EMOCK_NS::Functor(MockableHelper(function), #function, __FUNCTION__)
#else
#  define MOCKABLE(function)
#  define MCALL(function) function
#endif

#if defined(__cplusplus) && defined(EMOCK_USE_MOCKABLE)
#  include <emock/Functor.h>
#  define MOCKABLE_METHOD(cls, method) MOCKER(&cls::method).defaults().will(invoke(MockableConv(&cls::method))); \
                             PlaceHolder* cls##_method##_holder = MockableHelper(&cls::method); \
                             EMOCK_NS::MemFunctor<cls> method(cls##_method##_holder, "&" #cls "::" #method, __FUNCTION__, this)
#  define MCALL_METHOD(obj_ptr, cls, method) EMOCK_NS::MemFunctor<cls>(MockableHelper(&cls::method), "&" #cls "::" #method, __FUNCTION__, obj_ptr)
#else
#  define MOCKABLE_METHOD(cls, method)
#  define MCALL_METHOD(obj_ptr, cls, method) obj_ptr->method
#endif

#endif
