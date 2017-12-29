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

#ifndef __MOCKCPP_API_HOOK_MOCKER_H__
#define __MOCKCPP_API_HOOK_MOCKER_H__

#include <mockcpp/mockcpp.h>
#include <mockcpp/GlobalMockObject.h>
#include <mockcpp/ApiHookHolderFactory.h>

MOCKCPP_NS_START

template <typename API>
InvocationMockBuilderGetter mockAPI(const std::string& name, API* api)
{
    return MOCKCPP_NS::GlobalMockObject::instance.method
                 ( name
                 , reinterpret_cast<const void*>(api)
                 , ApiHookHolderFactory::create(api));
}

#ifdef _MSC_VER

  // MSVC use ecx register to transfer `this` pointer

  #define MOCKAPI_MEM_FUN_DEF(n)\
  template <typename R, typename CLS DECL_TEMPLATE_ARGS(n)>\
  InvocationMockBuilderGetter mockAPI(const std::string& name, R (CLS::*api)(DECL_ARGS(n)))\
  {\
      union {\
        R (*pf)(DECL_ARGS(n));\
        R (CLS::*pmf)(DECL_ARGS(n));\
      } u;\
      u.pmf = api;\
      return MOCKCPP_NS::GlobalMockObject::instance.method\
                   ( name\
                   , reinterpret_cast<const void*>(u.pf)\
                   , ApiHookHolderFactory::create<R(DECL_ARGS(n))>(u.pf));\
  }

#else

  // GCC use first arg that is pushed last to transfer `this` pointer

  #define MOCKAPI_MEM_FUN_DEF(n)\
  template <typename R, typename CLS DECL_TEMPLATE_ARGS(n)>\
  InvocationMockBuilderGetter mockAPI(const std::string& name, R (CLS::*api)(DECL_ARGS(n)))\
  {\
      union {\
        R (*pf)(CLS* DECL_REST_ARGS(n));\
        R (CLS::*pmf)(DECL_ARGS(n));\
      } u;\
      u.pmf = api;\
      return MOCKCPP_NS::GlobalMockObject::instance.method\
                   ( name\
                   , reinterpret_cast<const void*>(u.pf)\
                   , ApiHookHolderFactory::create<R(CLS* DECL_REST_ARGS(n))>(u.pf));\
  }

#endif

MOCKAPI_MEM_FUN_DEF(0)
MOCKAPI_MEM_FUN_DEF(1)
MOCKAPI_MEM_FUN_DEF(2)
MOCKAPI_MEM_FUN_DEF(3)
MOCKAPI_MEM_FUN_DEF(4)
MOCKAPI_MEM_FUN_DEF(5)
MOCKAPI_MEM_FUN_DEF(6)
MOCKAPI_MEM_FUN_DEF(7)
MOCKAPI_MEM_FUN_DEF(8)
MOCKAPI_MEM_FUN_DEF(9)
MOCKAPI_MEM_FUN_DEF(10)
MOCKAPI_MEM_FUN_DEF(11)
MOCKAPI_MEM_FUN_DEF(12)

MOCKCPP_NS_END

#endif

