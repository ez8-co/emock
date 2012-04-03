
#ifndef __TESTNGPP_WIN32_TEST_HIERARCHY_SANDBOX_RUNNER_H
#define __TESTNGPP_WIN32_TEST_HIERARCHY_SANDBOX_RUNNER_H

#include <string>

#include <testngpp/testngpp.h>
#include <testngpp/runner/TestHierarchyRunner.h>

TESTNGPP_NS_START

struct TestCaseRunner;
struct Win32TestHierarchySandboxRunnerImpl;

struct Win32TestHierarchySandboxRunner
   : public TestHierarchyRunner
{
   Win32TestHierarchySandboxRunner
         ( unsigned int maxCurrentProcess
         , TestCaseRunner*);

   ~Win32TestHierarchySandboxRunner();

	void run ( TestHierarchyHandler*
            , TestFixtureResultCollector*);

private:
   Win32TestHierarchySandboxRunnerImpl* This;
};

TESTNGPP_NS_END

#endif

