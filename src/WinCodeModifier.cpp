
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

