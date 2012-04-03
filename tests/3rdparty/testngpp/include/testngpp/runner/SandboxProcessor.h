
#ifndef __TESTNGPP_SANDBOX_PROCESSOR_H
#define __TESTNGPP_SANDBOX_PROCESSOR_H

#include <testngpp/testngpp.h>
#include <testngpp/runner/SandboxTypedef.h>

TESTNGPP_NS_START

struct EnvironmentCleaner;
struct SandboxHandler;

struct SandboxProcessor
{
	static void process(ChannelId rChannel, ChannelId wChannel, 
                  EnvironmentCleaner* cleaner, SandboxHandler* handler);
};

TESTNGPP_NS_END

#endif
