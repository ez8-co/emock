
#ifndef __TESTNGPP_TESTCASE_SANDBOX_H
#define __TESTNGPP_TESTCASE_SANDBOX_H

#include <testngpp/testngpp.h>

#include <testngpp/internal/Error.h>

#include <testngpp/runner/SandboxTypedef.h>
#include <testngpp/runner/EOFError.h>

TESTNGPP_NS_START

struct TestCaseInfoReader;
struct EnvironmentCleaner;
struct TestCase;
struct TestCaseRunner;
struct TestCaseResultCollector;
struct TestCaseSandboxImpl;

struct TestCaseSandbox
{
   SandboxId getSandboxId() const;
   ChannelId getChannelId() const;

   void handle() TESTNGPP_THROW(Error, EOFError);
   
   const TestCase* getTestCase() const;

   bool hasSucceeded() const;

   bool isDead() const;

   void cleanup();

   ~TestCaseSandbox();

public:

	static TestCaseSandbox*
	createInstance
         ( EnvironmentCleaner* cleaner
         , const TestCase* testcase
         , TestCaseRunner* runner
         , TestCaseResultCollector* collector
         , bool shouldReport);

private:
	TestCaseSandbox();

private:
   TestCaseSandboxImpl* This;
};

TESTNGPP_NS_END

#endif
