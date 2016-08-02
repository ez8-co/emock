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

#ifndef __MOCKCPP_ARGUMENTS_MACRO_HELPERS_H
#define __MOCKCPP_ARGUMENTS_MACRO_HELPERS_H

#include <mockcpp/RepeatMacros.h>

#define __ARG(n) MOCKP ## n
#define END_ARGS(n) __ARG(n)
#define ARGS(n) __ARG(n) ,
#define REST_ARGS(n) , __ARG(n)

#define __PARAM(n) p ## n
#define END_PARAMS(n) __PARAM(n)
#define PARAMS(n) __PARAM(n) ,
#define REST_PARAMS(n) , __PARAM(n)

#define TEMPLATE_ARG(n) typename __ARG(n)
#define TEMPLATE_ARGS(n) , TEMPLATE_ARG(n)
#define VOID_TEMPLATE_ARGS(n) typename __ARG(n),

#define __ARG_DECL(n) __ARG(n) __PARAM(n)
#define ARG_DECL(n) __ARG_DECL(n) ,
#define END_ARG_DECL(n) __ARG_DECL(n)
#define REST_ARG_DECL(n) , __ARG_DECL(n)

#define DECL_TEMPLATE_ARGS(n) SIMPLE_REPEAT(n, TEMPLATE_ARGS)
#define DECL_VARDIC_ARGS(n) SIMPLE_REPEAT(n, ARGS)
#define DECL_VARDIC_PARAM_LIST(n) SIMPLE_REPEAT(n, ARG_DECL)
#define DECL_VOID_TEMPLATE_ARGS(n) REPEAT(n, VOID_TEMPLATE_ARGS, TEMPLATE_ARG)
#define DECL_ARGS(n) REPEAT(n, ARGS, END_ARGS)
#define DECL_PARAMS(n) REPEAT(n, PARAMS, END_PARAMS)
#define DECL_PARAMS_LIST(n) REPEAT(n, ARG_DECL, END_ARG_DECL)

#define DECL_REST_ARGS(n) SIMPLE_REPEAT(n, REST_ARGS)
#define DECL_REST_PARAMS(n) SIMPLE_REPEAT(n, REST_PARAMS)
#define DECL_REST_ARG_DECL(n) SIMPLE_REPEAT(n, REST_ARG_DECL)
#endif

