
#ifndef __TESTNGPP_TEST_HIERARCHY_RUNNER_H
#define __TESTNGPP_TEST_HIERARCHY_RUNNER_H

#include <testngpp/testngpp.h>

TESTNGPP_NS_START

struct TestHierarchyHandler;
struct TestFixtureResultCollector;

struct TestHierarchyRunner
{
	virtual void run 
		( TestHierarchyHandler*
        , TestFixtureResultCollector*) = 0;

   virtual ~TestHierarchyRunner() {}
};

TESTNGPP_NS_END

#endif

