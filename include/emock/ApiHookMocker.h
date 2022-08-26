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

#ifndef __EMOCK_API_HOOK_MOCKER_H__
#define __EMOCK_API_HOOK_MOCKER_H__

#include <emock/emock.h>
#include <emock/GlobalMockObject.h>
#include <emock/ApiHookHolderFactory.h>
#include <emock/SymbolRetriever.h>

EMOCK_NS_START

template <typename MockerType>
InvocationMockBuilderGetter mockAPI(const char* matcher)
{
    std::string name;
    void* api = SymbolRetriever::getAddress(name, matcher);
    return EMOCK_NS::GlobalMockObject::instance.method
                 ( name
                 , reinterpret_cast<const void*>(api)
                 , ApiHookHolderFactory::create(reinterpret_cast<MockerType>(api)));
}

template <typename API>
InvocationMockBuilderGetter mockAPI(const std::string& name, API* api)
{
    return EMOCK_NS::GlobalMockObject::instance.method
                 ( name
                 , reinterpret_cast<const void*>(api)
                 , ApiHookHolderFactory::create(api));
}

#ifdef __GNUC__
  #define __cdecl /*__attribute__((cdecl))*/
  #define __stdcall /*__attribute__((stdcall))*/
#endif

#define _CC_BRANCH(type, cc) if(callingConv == #cc) {\
      return mockAPI<type(cc *)()>(m.c_str());\
    }
#define _RT_BRANCH(type) if(returnType == #type) {\
      _CC_BRANCH(type, ) else _CC_BRANCH(type, __cdecl) /*else _CC_BRANCH(type, __thiscall)*/ else _CC_BRANCH(type, __stdcall) else _CC_BRANCH(type, EMOCK_API)\
    }
#define RT_BRANCH(type) _RT_BRANCH(type) else _RT_BRANCH(type*)
#define INTERGRAL_RT_BRANCH(type) RT_BRANCH(type) else RT_BRANCH(unsigned type)

template <>
inline InvocationMockBuilderGetter mockAPI<const char>(const std::string&, const char* matcher)
{
    std::string m(matcher);
    std::string returnType("void");
    std::string::size_type from = m.find('{');
    if(from != std::string::npos) {
      std::string::size_type to = m.find('}', from);
      returnType = m.substr(from + 1, to - from - 1);
      m = m.replace(from, to - from + 1, "");
    }
    from = m.find('#');
    std::string callingConv;
    if(from != std::string::npos) {
      std::string::size_type to = m.find('#', from);
      callingConv = m.substr(from + 1, to - from - 1);
      m = m.replace(from, to - from + 1, "");
    }
    else {
      from = m.find('!');
      if(from != std::string::npos) {
        callingConv = "EMOCK_API";
        m = m.erase(from, 1);
      }
    }
    RT_BRANCH(void)
    else INTERGRAL_RT_BRANCH(char)
    else INTERGRAL_RT_BRANCH(short)
    else INTERGRAL_RT_BRANCH(int)
    else INTERGRAL_RT_BRANCH(long)
    else INTERGRAL_RT_BRANCH(long long)
    else RT_BRANCH(float)
    else RT_BRANCH(double)
    else RT_BRANCH(long double)
    else EMOCK_REPORT_FAILURE(std::string("Unsupported return type {").append(returnType.c_str()).append("}, use EMOCKX(")
      .append(returnType.c_str()).append(", \"").append(m.c_str()).append("\") instead.").c_str());
}

#undef INTERGRAL_RT_BRANCH
#undef RT_BRANCH
#undef _RT_BRANCH
#undef _CC_BRANCH

// MSVC use ecx register to transfer `this` pointer
// In Windows: `__thiscall` is left-to-right 
//             and almost equal to `__stdcall` by `ret 8` when return

// GCC push `this` at last to transfer `this` pointer
// so we add first arg and use right-to-left `__cdecl` as mocker

#define MOCKAPI_MEM_FUN_DEF(n)\
template <typename R, typename CLS DECL_TEMPLATE_ARGS(n)>\
InvocationMockBuilderGetter mockAPI(const std::string& name, R (CLS::*api)(DECL_ARGS(n)))\
{\
    union {\
      R (CLS::*pmf)(DECL_ARGS(n));\
      R (EMOCK_API *pf)(CLS* DECL_REST_ARGS(n));\
      void* p;\
    } u;\
    u.pmf = api;\
    u.p = SymbolRetriever::getMethodAddress(u.p, typeid(api), name);\
    return EMOCK_NS::GlobalMockObject::instance.method\
                 ( name\
                 , u.p\
                 , ApiHookHolderFactory::create<R EMOCK_API (CLS* DECL_REST_ARGS(n))>(u.pf)\
                 , true);\
}

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

#undef MOCKAPI_MEM_FUN_DEF

#define MOCKAPI_CONST_MEM_FUN_DEF(n)\
template <typename R, typename CLS DECL_TEMPLATE_ARGS(n)>\
InvocationMockBuilderGetter mockAPI(const std::string& name, R (CLS::*api)(DECL_ARGS(n)) const)\
{\
    union {\
      R (CLS::*pmf)(DECL_ARGS(n)) const;\
      R (EMOCK_API *pf)(const CLS* DECL_REST_ARGS(n));\
      void* p;\
    } u;\
    u.pmf = api;\
    u.p = SymbolRetriever::getMethodAddress(u.p, typeid(api), name);\
    return EMOCK_NS::GlobalMockObject::instance.method\
                 ( name\
                 , u.p\
                 , ApiHookHolderFactory::create<R EMOCK_API (const CLS* DECL_REST_ARGS(n))>(u.pf)\
                 , true);\
}

MOCKAPI_CONST_MEM_FUN_DEF(0)
MOCKAPI_CONST_MEM_FUN_DEF(1)
MOCKAPI_CONST_MEM_FUN_DEF(2)
MOCKAPI_CONST_MEM_FUN_DEF(3)
MOCKAPI_CONST_MEM_FUN_DEF(4)
MOCKAPI_CONST_MEM_FUN_DEF(5)
MOCKAPI_CONST_MEM_FUN_DEF(6)
MOCKAPI_CONST_MEM_FUN_DEF(7)
MOCKAPI_CONST_MEM_FUN_DEF(8)
MOCKAPI_CONST_MEM_FUN_DEF(9)
MOCKAPI_CONST_MEM_FUN_DEF(10)
MOCKAPI_CONST_MEM_FUN_DEF(11)
MOCKAPI_CONST_MEM_FUN_DEF(12)

#undef MOCKAPI_CONST_MEM_FUN_DEF

EMOCK_NS_END

#endif

