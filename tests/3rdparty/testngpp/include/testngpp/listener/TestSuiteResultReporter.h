
#ifndef __TESTNGPP_TEST_SUITE_RESULT_REPORTER_H
#define __TESTNGPP_TEST_SUITE_RESULT_REPORTER_H

#include <testngpp/testngpp.h>

TESTNGPP_NS_START

struct TestSuiteInfoReader;

struct TestSuiteResultReporter
{
   ////////////////////////////////////////////////////////////
   virtual int getNumberOfTestCases(TestSuiteInfoReader*) const = 0;
   virtual int getNumberOfSuccessfulTestCases(TestSuiteInfoReader*) const = 0;
   virtual int getNumberOfUnsuccessfulTestCases(TestSuiteInfoReader*) const = 0;
   virtual int getNumberOfFailedTestCases(TestSuiteInfoReader*) const = 0;
   virtual int getNumberOfErrorTestCases(TestSuiteInfoReader*) const = 0;
   virtual int getNumberOfCrashedTestCases(TestSuiteInfoReader*) const = 0;
   virtual int getNumberOfSkippedTestCases(TestSuiteInfoReader*) const = 0;

   virtual int getNumberOfFixtures(TestSuiteInfoReader*) const = 0;
   virtual int getNumberOfFixtureErrors(TestSuiteInfoReader*) const = 0;
   virtual int getNumberOfFixtureFailures(TestSuiteInfoReader*) const = 0;

   virtual int getNumberOfSuiteErrors(TestSuiteInfoReader*) const = 0;

   virtual ~TestSuiteResultReporter() {}

};

TESTNGPP_NS_END

#endif

