
#ifndef __TESTNGPP_SIMPLE_TEST_CASE_RUNNER_H
#define __TESTNGPP_SIMPLE_TEST_CASE_RUNNER_H

#include <testngpp/testngpp.h>
#include <testngpp/runner/TestCaseRunner.h>

TESTNGPP_NS_START

struct SimpleTestCaseRunner
	: public TestCaseRunner
{
	bool run(TestCase*, TestCaseResultCollector*, bool reportSuccess=true);
};

TESTNGPP_NS_END

#endif

