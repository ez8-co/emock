
#ifndef __TESTNGPP_SANDBOX_H
#define __TESTNGPP_SANDBOX_H

#include <testngpp/testngpp.h>
#include <testngpp/runner/SandboxTypedef.h>

TESTNGPP_NS_START

struct EnvironmentCleaner;
struct SandboxImpl;
struct SandboxHandler;

struct Sandbox
{
   SandboxId getSandboxId() const;
   ChannelId getChannelId() const;

   bool isDead() const;
   void die();

   void cleanup();

   ~Sandbox();

	static Sandbox*
	createInstance(EnvironmentCleaner* cleaner, SandboxHandler* childHandler);

private:
	Sandbox();

private:
   SandboxImpl* This;
};

TESTNGPP_NS_END

#endif
