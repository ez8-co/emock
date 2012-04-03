
#ifndef __TESTNGPP_TEST_SUITE_RUNNER_H
#define __TESTNGPP_TEST_SUITE_RUNNER_H

#include <string>

#include <testngpp/testngpp.h>

TESTNGPP_NS_START

struct TestSuiteContext;
struct TestCaseFilter;
struct TestFixtureRunner;
struct TestResultCollector;

struct TestSuiteRunnerImpl;

struct TestSuiteRunner
{
	TestSuiteRunner( TestFixtureRunner*
                  , TestResultCollector* );
	~TestSuiteRunner();

   void run(TestSuiteContext* suite
            , const TestCaseFilter* filter);
private:
	TestSuiteRunnerImpl* This;

};

TESTNGPP_NS_END

#endif

