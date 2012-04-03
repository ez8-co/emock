
#ifndef __TESTNGPP_SIMPLE_TEST_RESULT_REPORTER_H
#define __TESTNGPP_SIMPLE_TEST_RESULT_REPORTER_H

#include <testngpp/testngpp.h>

#include <testngpp/listener/TestListener.h>
#include <testngpp/listener/TestResultReporter.h>

TESTNGPP_NS_START

struct TestSuiteResultReporter;
struct SimpleTestResultReporterImpl;

struct SimpleTestResultReporter
   : public TestResultReporter
   , public TestListener
{
	SimpleTestResultReporter(TestSuiteResultReporter*);
	~SimpleTestResultReporter();

   unsigned int getNumberOfTestCases() const;
   unsigned int getNumberOfSuccessfulTestCases() const;
   unsigned int getNumberOfUnsuccessfulTestCases() const;
   unsigned int getNumberOfFailedTestCases() const;
   unsigned int getNumberOfErrorTestCases() const;
   unsigned int getNumberOfSkippedTestCases() const;
   unsigned int getNumberOfCrashedTestCases() const;
   unsigned int getNumberOfLoadedSuites() const;
   unsigned int getNumberOfUnloadableSuites() const;
   unsigned int getNumberOfErrorFixtures() const;

   void addCaseError(const TestCaseInfoReader*, const std::string&);
   void addCaseCrash(const TestCaseInfoReader*);
   void addCaseSkipped(const TestCaseInfoReader*);
   void addCaseFailure(const TestCaseInfoReader*, const AssertionFailure&);

   void startTestCase(const TestCaseInfoReader*);
   void endTestCase(const TestCaseInfoReader*, unsigned int, unsigned int);

   void startTestFixture(TestFixtureInfoReader*);
   void endTestFixture(TestFixtureInfoReader*);
   void addFixtureError(TestFixtureInfoReader*, const std::string&);
   void addFixtureFailure(TestFixtureInfoReader*, const AssertionFailure&);

   void startTestSuite(TestSuiteInfoReader*);
   void endTestSuite(TestSuiteInfoReader*);
   void addSuiteError(TestSuiteInfoReader*, const std::string&);

   void startTagsFiltering(const TagsFilterRule*);
   void endTagsFiltering(const TagsFilterRule*);

   void startTest();
   void endTest(unsigned int, unsigned int);
   void addError(const std::string&);

private:

   SimpleTestResultReporterImpl* This;
};

TESTNGPP_NS_END

#endif

