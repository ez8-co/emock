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

#include "JmpCode.h"

#ifdef _MSC_VER // [
   #ifdef _WIN64 // [
      typedef unsigned __int64  uintptr_t;
   #else // _WIN64 ][
      typedef _W64 unsigned int uintptr_t;
   #endif // _WIN64 ]
#else
   #include <inttypes.h>
#endif // _MSC_VER ]

const unsigned char jmpCodeTemplate[]  = { 0xE9, 0x00, 0x00, 0x00, 0x00 };

inline void set_jmp_code(unsigned char base[], const void* from, const void* to)
{
  *(unsigned int*)&base[1] = (unsigned int)((uintptr_t)to - (uintptr_t)from - sizeof(jmpCodeTemplate));
}

// FF 25 : JMP /4   jmp absolute indirect
// bytes 2 ~ 5 : operand of jmp, relative to the memory that recorded the thunk addr. it should be zero.
// bytes 6 ~ 13 : the absolute addr of thunk.
const unsigned char jmpCodeTemplateLong[]  =
   { 0xFF, 0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

inline void set_jmp_code_long(unsigned char base[], const void* from, const void* to)
{
 *(uintptr_t *)&base[6] = (uintptr_t)to;
}

static const size_t kMaxAllocationDelta = 0x80000000; // 2GB

EMOCK_NS_START

#if BUILD_FOR_X64
   #define JMP_CODE_SIZE sizeof(jmpCodeTemplateLong)
#elif BUILD_FOR_X86
   #define JMP_CODE_SIZE sizeof(jmpCodeTemplate)
#endif

struct JmpCodeImpl
{
   ////////////////////////////////////////////////
   JmpCodeImpl(const void* from, const void* trampoline, const void* to)
   {
      if(trampoline) {
         ::memcpy(m_code, jmpCodeTemplate, sizeof(jmpCodeTemplate));
         set_jmp_code(m_code, from, trampoline);
      }
      else if((uintptr_t)to - (uintptr_t)from <= kMaxAllocationDelta) {
         ::memcpy(m_code, jmpCodeTemplate, sizeof(jmpCodeTemplate));
         set_jmp_code(m_code, from, to);
      } else {
         ::memcpy(m_code, jmpCodeTemplateLong, sizeof(jmpCodeTemplateLong));
         set_jmp_code_long(m_code, from, to);
      }
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
JmpCode::JmpCode(const void* from, const void* trampoline, const void* to)
   : This(new JmpCodeImpl(from, trampoline, to))
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

EMOCK_NS_END

