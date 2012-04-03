
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <sstream>

#include <testngpp/comm/PipeReadableChannel.h>

TESTNGPP_NS_START

//////////////////////////////////////////////////////////////////
PipeReadableChannel::PipeReadableChannel(int pipeFd, bool autoClose)
   : fd(pipeFd), shouldClose(autoClose)
{}

//////////////////////////////////////////////////////////////////
PipeReadableChannel::~PipeReadableChannel()
{
   if(shouldClose) ::close(fd);
}

//////////////////////////////////////////////////////////////////
static void readFromPipe(int fd, void* buf, size_t size)
{
   int result = 0;

   do {
      result = ::read(fd, buf, size);
   } while(result < 0 && errno == EAGAIN);
   
   if(result < 0)
   {
      throw Error(::strerror(errno));
   }
   
   if(result == 0)
   {
      throw EOFError();
   }
}
//////////////////////////////////////////////////////////////////
unsigned char PipeReadableChannel::readByte() TESTNGPP_THROW(Error, EOFError)
{
   unsigned char byte;

   readFromPipe(fd, &byte, 1);

   return byte;
}

//////////////////////////////////////////////////////////////////
int PipeReadableChannel::readInt() TESTNGPP_THROW(Error, EOFError)
{
   int value;

   readFromPipe(fd, &value, sizeof(value));

   return value;
}

//////////////////////////////////////////////////////////////////
std::string PipeReadableChannel::readString() TESTNGPP_THROW(Error, EOFError)
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
int PipeReadableChannel::getFD() const
{
   return fd;
}

//////////////////////////////////////////////////////////////////
void PipeReadableChannel::close() 
{
   (void) ::close(fd);
}

//////////////////////////////////////////////////////////////////

TESTNGPP_NS_END

