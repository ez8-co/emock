
#ifndef __TESTNGPP_TESTCASE_SANDBOX_HANDLER_H
#define __TESTNGPP_TESTCASE_SANDBOX_HANDLER_H

#include <testngpp/testngpp.h>

#include <testngpp/runner/SandboxHandler.h>

TESTNGPP_NS_START

struct TestCase;
struct TestCaseRunner;
struct TestCaseSandboxHandlerImpl;

struct TestCaseSandboxHandler : public SandboxHandler
{
   TestCaseSandboxHandler
         ( const TestCase* testcase
         , TestCaseRunner* runner);

   ~TestCaseSandboxHandler();

   void handle(ChannelId channelId);

private:

   TestCaseSandboxHandlerImpl* This;
};

TESTNGPP_NS_END

#endif

