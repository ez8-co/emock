
#ifndef __TESTNGPP_SIMPLE_TEST_CASE_RESULT_REPORTER_H
#define __TESTNGPP_SIMPLE_TEST_CASE_RESULT_REPORTER_H

#include <testngpp/testngpp.h>

#include <testngpp/listener/TestCaseListener.h>
#include <testngpp/listener/TestCaseResultReporter.h>

TESTNGPP_NS_START

struct SimpleTestCaseResultReporterImpl;

struct SimpleTestCaseResultReporter
   : public TestCaseResultReporter
   , public TestCaseListener
{
	SimpleTestCaseResultReporter();
	~SimpleTestCaseResultReporter();

   unsigned int getTestCaseResult(const TestCaseInfoReader*) const;

   void addCaseError(const TestCaseInfoReader*, const std::string&);
   void addCaseCrash(const TestCaseInfoReader*);
   void addCaseSkipped(const TestCaseInfoReader*);
   void addCaseFailure(const TestCaseInfoReader*, const AssertionFailure&);

   void startTestCase(const TestCaseInfoReader*);
   void endTestCase(const TestCaseInfoReader*, unsigned int, unsigned int);

private:
   SimpleTestCaseResultReporterImpl * This;
};

TESTNGPP_NS_END

#endif

