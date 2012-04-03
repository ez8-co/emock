
#include <sstream>

#include <testngpp/comm/Win32PipeReadableChannel.h>
#include <testngpp/win32/Win32ThrowLastError.h>

#if defined(_MSC_VER)
#define snprintf _snprintf
#endif

TESTNGPP_NS_START

//////////////////////////////////////////////////////////////////
Win32PipeReadableChannel::Win32PipeReadableChannel(HANDLE readableHandle, bool autoClose)
   : handle(readableHandle), shouldClose(autoClose), hasBeenClosed(false)
{}

//////////////////////////////////////////////////////////////////
Win32PipeReadableChannel::~Win32PipeReadableChannel()
{
   if(shouldClose) close();
}

//////////////////////////////////////////////////////////////////
static void readFromPipe(HANDLE handle, unsigned char* buf, size_t size)
{
   BOOL bSuccess = FALSE;
 
   size_t readSize = size;
   DWORD haveRead = 0;
   do
   { 
      bSuccess = ReadFile(handle, &buf[haveRead], readSize, &haveRead, NULL);
	  readSize -= haveRead;
   } while(!bSuccess && GetLastError() == ERROR_IO_PENDING); 
    
   if(!bSuccess)
   {
	   if(GetLastError() == ERROR_BROKEN_PIPE)
	   {
          throw EOFError();
	   }
	   else
	   {
		   throwLastError();
	   }
   }
}
//////////////////////////////////////////////////////////////////
unsigned char Win32PipeReadableChannel::readByte() TESTNGPP_THROW(Error, EOFError)
{
   unsigned char byte;

   readFromPipe(handle, &byte, 1);

   return byte;
}

//////////////////////////////////////////////////////////////////
int Win32PipeReadableChannel::readInt() TESTNGPP_THROW(Error, EOFError)
{
   int value;

   readFromPipe(handle, (unsigned char*)&value, sizeof(value));

   return value;
}

//////////////////////////////////////////////////////////////////
std::string Win32PipeReadableChannel::readString() TESTNGPP_THROW(Error, EOFError)
{
   std::stringstream ss;

   unsigned char byte = 0;
   while((byte = readByte()) != '\0')
   {
      char buf[2];
      ::snprintf(buf, sizeof(buf), "%c", byte);
      ss << buf;
   }

   return ss.str();
}

//////////////////////////////////////////////////////////////////
HANDLE Win32PipeReadableChannel::getHandle() const
{
   return handle;
}

//////////////////////////////////////////////////////////////////
void Win32PipeReadableChannel::close() 
{
	if(!hasBeenClosed)
	{
		(void) ::CloseHandle(handle);
		hasBeenClosed = true;
	}
}

//////////////////////////////////////////////////////////////////

TESTNGPP_NS_END

