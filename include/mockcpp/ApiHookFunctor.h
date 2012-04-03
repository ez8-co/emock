
#ifndef __MOCKCPP_API_HOOK_FUNCTOR_H__
#define __MOCKCPP_API_HOOK_FUNCTOR_H__

#include <mockcpp/mockcpp.h>
#include <mockcpp/GlobalMockObject.h>

MOCKCPP_NS_START

/////////////////////////////////////////////////////
template <typename F, unsigned int Seq>
struct ApiHookFunctor
{
};

const std::string empty_caller("");
#define __MOCKCPP_API_HOOK_FUNCTOR_DEF(n, CallingConvention) \
template <typename R DECL_TEMPLATE_ARGS(n), unsigned int Seq> \
struct ApiHookFunctor<R CallingConvention (DECL_ARGS(n)), Seq> \
{ \
private: \
   typedef R CallingConvention F (DECL_ARGS(n)); \
 \
   static R CallingConvention hook(DECL_PARAMS_LIST(n)) \
   { \
      return GlobalMockObject::instance.invoke<R>(apiAddress) \
                                (empty_caller DECL_REST_PARAMS(n)); \
   } \
 \
   static bool appliedBy(F* api) \
   { return apiAddress == reinterpret_cast<void*>(api); } \
 \
   static void* getHook() \
   { return reinterpret_cast<void*>(hook); } \
 \
   static void freeHook() \
   { if(--refCount == 0) apiAddress = 0; } \
public: \
 \
   static void* getApiHook(F* api) \
   { \
      if(!appliedBy(api)) return 0; \
      ++refCount; \
      return getHook(); \
   } \
 \
   static void* applyApiHook(F* api) \
   { \
      if(apiAddress != 0) return 0; \
      apiAddress = reinterpret_cast<void*>(api); \
      refCount = 1; \
      return getHook(); \
   } \
 \
   static bool freeApiHook(void* hook) \
   { \
       if(getHook() != hook) return false; \
       freeHook(); \
       return true; \
   } \
private: \
   static void* apiAddress; \
   static unsigned int refCount; \
}; \
template <typename R DECL_TEMPLATE_ARGS(n), unsigned int Seq> \
void* ApiHookFunctor<R CallingConvention (DECL_ARGS(n)), Seq>::apiAddress = 0; \
template <typename R DECL_TEMPLATE_ARGS(n), unsigned int Seq> \
unsigned int ApiHookFunctor<R CallingConvention (DECL_ARGS(n)), Seq>::refCount = 0 

#if defined(_MSC_VER)
#define MOCKCPP_API_HOOK_FUNCTOR_DEF(n) \
__MOCKCPP_API_HOOK_FUNCTOR_DEF(n, ); \
__MOCKCPP_API_HOOK_FUNCTOR_DEF(n, __stdcall) 
#else
#define MOCKCPP_API_HOOK_FUNCTOR_DEF(n) \
__MOCKCPP_API_HOOK_FUNCTOR_DEF(n, )
#endif

MOCKCPP_API_HOOK_FUNCTOR_DEF(0);
MOCKCPP_API_HOOK_FUNCTOR_DEF(1);
MOCKCPP_API_HOOK_FUNCTOR_DEF(2);
MOCKCPP_API_HOOK_FUNCTOR_DEF(3);
MOCKCPP_API_HOOK_FUNCTOR_DEF(4);
MOCKCPP_API_HOOK_FUNCTOR_DEF(5);
MOCKCPP_API_HOOK_FUNCTOR_DEF(6);
MOCKCPP_API_HOOK_FUNCTOR_DEF(7);
MOCKCPP_API_HOOK_FUNCTOR_DEF(8);
MOCKCPP_API_HOOK_FUNCTOR_DEF(9);
MOCKCPP_API_HOOK_FUNCTOR_DEF(10);
MOCKCPP_API_HOOK_FUNCTOR_DEF(11);
MOCKCPP_API_HOOK_FUNCTOR_DEF(12);

MOCKCPP_NS_END

#endif

