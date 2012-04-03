
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include <testngpp/runner/EnvironmentCleaner.h>
#include <testngpp/runner/SandboxHandler.h>
#include <testngpp/runner/SandboxProcessor.h>
#include <testngpp/comm/PipeReadableChannel.h>

TESTNGPP_NS_START

namespace {
   
   void waitForStartup(int fd)
   {
      PipeReadableChannel channel(fd, false);
      channel.readByte();
   }
}

void
SandboxProcessor::process(ChannelId rChannel, ChannelId wChannel, \
        EnvironmentCleaner* cleaner, SandboxHandler* childHandler)
{
   cleaner->cleanUp();

   ::close(rChannel);
   int channel = ::dup(wChannel);
   ::close(wChannel);

//   waitForStartup(channel);

   childHandler->handle(channel);

   ::close(channel);
}

TESTNGPP_NS_END

