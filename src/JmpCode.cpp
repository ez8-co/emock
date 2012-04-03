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

