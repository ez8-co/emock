
#ifndef __TESTNGPP_TEST_FIXTURE_RESULT_COLLECTOR_H
#define __TESTNGPP_TEST_FIXTURE_RESULT_COLLECTOR_H

#include <testngpp/testngpp.h>

#include <testngpp/listener/TestCaseResultCollector.h>

TESTNGPP_NS_START

struct TestFixtureInfoReader;

struct TestFixtureResultCollector
	: public TestCaseResultCollector
{
   virtual void startTestFixture(TestFixtureInfoReader*) = 0;
   virtual void endTestFixture(TestFixtureInfoReader*) = 0;

   virtual void addFixtureError(TestFixtureInfoReader*, const std::string&) = 0;
	virtual void addFixtureFailure(TestFixtureInfoReader*, const AssertionFailure&) = 0;

	virtual ~TestFixtureResultCollector() {}
};

TESTNGPP_NS_END

#endif

