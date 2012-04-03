
#ifndef __MOCKCPP_PARAMETERIZED_API_HOOK_HOLDER_H__
#define __MOCKCPP_PARAMETERIZED_API_HOOK_HOLDER_H__

#include <mockcpp/ApiHookHolder.h>
#include <mockcpp/ApiHookGenerator.h>

MOCKCPP_NS_START

/////////////////////////////////////////////////////
template <typename F>
struct ParameterizedApiHookHolder 
   : public ApiHookHolder
{
   const static unsigned int maxSeq = 10;

   ParameterizedApiHookHolder(F* api) 
   {
      (m_hook = ApiHookGenerator<F, maxSeq>::findApiHook(api)) ||
      (m_hook = ApiHookGenerator<F, maxSeq>::appyApiHook(api)); 
   }

   void * getApiHook() const
   { return m_hook; }

   ~ParameterizedApiHookHolder() 
   {
      ApiHookGenerator<F, maxSeq>::freeApiHook(m_hook);
   }

private:
   void* m_hook;
};

MOCKCPP_NS_END

#endif

