
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
