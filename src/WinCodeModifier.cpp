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

#include <Windows.h>

#include <emock/CodeModifier.h>

EMOCK_NS_START

bool CodeModifier::modify(void *dest, const void *src, size_t size)
{
	DWORD  dwOldProtect(0);
	DWORD  dwReadWrite(PAGE_EXECUTE_READWRITE); // modify code segment must use PAGE_EXECUTE_READWRITE.

	BOOL  bRet = ::VirtualProtect(dest, size, dwReadWrite, &dwOldProtect);
	bRet =  bRet && 
		::WriteProcessMemory( ::GetCurrentProcess(), dest, src,  size, NULL );
	bRet =  bRet && 
		::VirtualProtect(dest, size, dwOldProtect, &dwReadWrite);
	return (bRet == TRUE);
}


EMOCK_NS_END

