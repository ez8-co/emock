
#ifndef __TESTNGPP_WIN32_SANDBOX_H
#define __TESTNGPP_WIN32_SANDBOX_H

#include <windows.h>
#include <string>

#include <testngpp/testngpp.h>

TESTNGPP_NS_START

struct TestCase;
struct Win32SandboxImpl;

struct Win32Sandbox
{
   HANDLE getSandboxId() const;
   HANDLE getChannelId() const;
   HANDLE getEventId() const;

   bool isDead() const;
   void die();

   void cleanup();

   ~Win32Sandbox();

	static Win32Sandbox*
	createInstance
	   ( const std::string& suitePath
	   , const TestCase* testcase);

private:
	Win32Sandbox();

private:
   Win32SandboxImpl* This;
};

TESTNGPP_NS_END

#endif
