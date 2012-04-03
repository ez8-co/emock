
#ifndef __TESTNGPP_SANDBOX_HANDLER_H
#define __TESTNGPP_SANDBOX_HANDLER_H

#include <testngpp/testngpp.h>
#include <testngpp/runner/SandboxTypedef.h>

TESTNGPP_NS_START

struct SandboxHandler
{
   virtual void handle(ChannelId channelId) = 0;

   virtual ~SandboxHandler() {}
};

TESTNGPP_NS_END

#endif
