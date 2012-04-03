/***
    mockcpp is a generic C/C++ mock framework.
    Copyright (C) <2010>  <Darwin Yuan: darwin.yuan@gmail.com>
	                      <Chen Guodong: sinojelly@gmail.com>

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

#include <string.h>

#include "JmpOnlyApiHook.h"
#include <mockcpp/JmpCode.h>
#include <mockcpp/CodeModifier.h>

MOCKCPP_NS_START

////////////////////////////////////////////////////////
struct JmpOnlyApiHookImpl
{
   /////////////////////////////////////////////////////
   JmpOnlyApiHookImpl
              ( const void* api
              , const void* stub)
		: m_jmpCode(api, stub)
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
              , const void* stub )
	: This(new JmpOnlyApiHookImpl(api, stub))
{
}

/////////////////////////////////////////////////////////////////
JmpOnlyApiHook::~JmpOnlyApiHook()
{
	delete This;
}

/////////////////////////////////////////////////////////////////

MOCKCPP_NS_END

