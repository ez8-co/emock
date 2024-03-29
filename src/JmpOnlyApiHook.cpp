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

#include <string.h>

#include "JmpOnlyApiHook.h"
#include "JmpCode.h"
#include "CodeModifier.h"

EMOCK_NS_START

////////////////////////////////////////////////////////
struct JmpOnlyApiHookImpl
{
   /////////////////////////////////////////////////////
   JmpOnlyApiHookImpl
              ( const void* api
              , const void* trampoline
              , const void* stub)
		: m_jmpCode(api, trampoline, stub)
        , m_originalData(0)
        , m_api(api)
   {
      startHook();
   }

   /////////////////////////////////////////////////////
   ~JmpOnlyApiHookImpl()
   {
      stopHook();
   }

   /////////////////////////////////////////////////////
   void saveOriginalData()
   {
      m_originalData = new char[m_jmpCode.getCodeSize()];
      ::memcpy(m_originalData, m_api, m_jmpCode.getCodeSize());
   }

   /////////////////////////////////////////////////////
   void startHook()
   {
      saveOriginalData();
      changeCode(m_jmpCode.getCodeData());
   }

   /////////////////////////////////////////////////////
   void stopHook()
   {
      changeCode(m_originalData);
      delete [] m_originalData;
   }

   /////////////////////////////////////////////////////
   void changeCode(const void* data)
   {
      CodeModifier::modify(const_cast<void*>(m_api), data, m_jmpCode.getCodeSize());
   }

   /////////////////////////////////////////////////////
   JmpCode m_jmpCode;
   char* m_originalData;
   const void* m_api;
};

/////////////////////////////////////////////////////////////////
JmpOnlyApiHook::JmpOnlyApiHook 
              ( const void* api
              , const void* trampoline
              , const void* stub )
	: This(new JmpOnlyApiHookImpl(api, trampoline, stub))
{
}

/////////////////////////////////////////////////////////////////
JmpOnlyApiHook::~JmpOnlyApiHook()
{
	delete This;
}

/////////////////////////////////////////////////////////////////

EMOCK_NS_END

