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

#include <inttypes.h>
#include <string.h>

#include <mockcpp/JmpCode.h>
#include "JmpCodeArch.h"

MOCKCPP_NS_START

#define JMP_CODE_SIZE sizeof(jmpCodeTemplate)

struct JmpCodeImpl
{
   ////////////////////////////////////////////////
   JmpCodeImpl(const void* from, const void* to)
   {
      ::memcpy(m_code, jmpCodeTemplate, JMP_CODE_SIZE);
      SET_JMP_CODE(m_code, from, to);
   }

   ////////////////////////////////////////////////
   void*  getCodeData() const
   {
      return (void*) m_code;
   }

   ////////////////////////////////////////////////
   size_t getCodeSize() const
   {
      return JMP_CODE_SIZE;
   }

   ////////////////////////////////////////////////

   unsigned char m_code[JMP_CODE_SIZE];
};

///////////////////////////////////////////////////
JmpCode::JmpCode(const void* from, const void* to)
   : This(new JmpCodeImpl(from, to))
{
}

///////////////////////////////////////////////////
JmpCode::~JmpCode()
{
   delete This;
}

///////////////////////////////////////////////////
void*
JmpCode::getCodeData() const
{
   return This->getCodeData();
}

///////////////////////////////////////////////////
size_t
JmpCode::getCodeSize() const
{
   return This->getCodeSize();
}

MOCKCPP_NS_END

