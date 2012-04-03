
#if defined(_MSC_VER)
#include <windows.h>

#include <testngpp/internal/Error.h>

TESTNGPP_NS_START

void throwLastError()
{
    LPVOID lpMsgBuf;

    DWORD dw = GetLastError(); 

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

	std::string errorMsg((const char*)lpMsgBuf);
    
	LocalFree(lpMsgBuf);

	throw Error(errorMsg);
}

TESTNGPP_NS_END

#endif
