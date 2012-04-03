
#ifndef __TESTNGPP_SIMPLE_TEST_HIERARCHY_RUNNER_H
#define __TESTNGPP_SIMPLE_TEST_HIERARCHY_RUNNER_H

#include <testngpp/runner/TestHierarchyRunner.h>

TESTNGPP_NS_START

///////////////////////////////////////////////////////

struct TestHierarchyHandler;
struct TestFixtureResultCollector;
struct TestCaseRunner;

struct SimpleTestHierarchyRunnerImpl;

struct SimpleTestHierarchyRunner : public TestHierarchyRunner
{
	SimpleTestHierarchyRunner(TestCaseRunner* runner);
	~SimpleTestHierarchyRunner();

	void run( TestHierarchyHandler* 
           , TestFixtureResultCollector*);

private:
   SimpleTestHierarchyRunnerImpl * This;
};

///////////////////////////////////////////////////////

TESTNGPP_NS_END

#endif

