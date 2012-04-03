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

#include <Windows.h>

#include <mockcpp/CodeModifier.h>

MOCKCPP_NS_START

bool CodeModifier::modify(void *dest, const void *src, size_t size)
{
	DWORD  dwOldProtect(0);
	DWORD  dwReadWrite(PAGE_EXECUTE_READWRITE); // modify code segment must use PAGE_EXECUTE_READWRITE.

	BOOL  bRet = TRUE;
	bRet = ::VirtualProtect(dest, size, dwReadWrite, &dwOldProtect);
	bRet =  bRet && 
		::WriteProcessMemory( ::GetCurrentProcess(), dest, src,  size, NULL );
	bRet =  bRet && 
		::VirtualProtect(dest, size, dwOldProtect, &dwReadWrite);
	return (bRet == TRUE);
}


MOCKCPP_NS_END

