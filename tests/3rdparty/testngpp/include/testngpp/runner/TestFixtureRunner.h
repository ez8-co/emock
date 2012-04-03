
#ifndef __TESTNGPP_TEST_FIXTURE_RUNNER_H__
#define __TESTNGPP_TEST_FIXTURE_RUNNER_H__

#include <string>

#include <testngpp/testngpp.h>

TESTNGPP_NS_START

struct TestFixtureContext;
struct TestFixtureResultCollector;
struct TestHierarchyRunner;
struct TestCaseFilter;
struct TestFixtureRunnerImpl;

struct TestFixtureRunner
{
   TestFixtureRunner(TestHierarchyRunner* runner);
   ~TestFixtureRunner();

   void run ( TestFixtureContext *
            , TestFixtureResultCollector*
            , const TestCaseFilter*
			, const std::string&);

private:
   TestFixtureRunnerImpl* This;
};

TESTNGPP_NS_END

#endif

