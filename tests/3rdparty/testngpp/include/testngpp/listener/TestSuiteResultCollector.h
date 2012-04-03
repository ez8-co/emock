
#ifndef __TESTNGPP_TEST_SUITE_RESULT_COLLECTOR_H
#define __TESTNGPP_TEST_SUITE_RESULT_COLLECTOR_H

#include <testngpp/testngpp.h>

#include <testngpp/listener/TestFixtureResultCollector.h>

TESTNGPP_NS_START

struct TestSuiteInfoReader;

struct TestSuiteResultCollector
	: public TestFixtureResultCollector
{
   virtual void startTestSuite(TestSuiteInfoReader*) = 0;
   virtual void endTestSuite(TestSuiteInfoReader*) = 0;
   virtual void addSuiteError(TestSuiteInfoReader*, const std::string&) = 0;

	virtual ~TestSuiteResultCollector() {}
};

TESTNGPP_NS_END

#endif

