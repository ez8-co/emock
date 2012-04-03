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

