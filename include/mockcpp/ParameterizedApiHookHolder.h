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

