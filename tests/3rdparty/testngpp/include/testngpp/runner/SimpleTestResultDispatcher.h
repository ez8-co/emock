
#ifndef __TESTNGPP_SIMPLE_TEST_RESULT_DISPATCHER_H
#define __TESTNGPP_SIMPLE_TEST_RESULT_DISPATCHER_H

#include <testngpp/testngpp.h>

#include <testngpp/listener/TestResultCollector.h>
#include <testngpp/listener/TestResultReporter.h>

#include <testngpp/runner/TestResultDispatcher.h>
#include <testngpp/runner/TestSuiteResultDispatcher.h>
#include <testngpp/runner/TestCaseResultDispatcher.h>

TESTNGPP_NS_START

struct TestSuiteInfoReader;
struct SimpleTestResultDispatcherImpl;

struct SimpleTestResultDispatcher
   : public TestResultDispatcher
   , public TestSuiteResultDispatcher
   , public TestCaseResultDispatcher
   , public TestResultCollector
{
   SimpleTestResultDispatcher();
   ~SimpleTestResultDispatcher();

   void registerListener(TestListener* listner);

   void registerTestSuiteListener(TestSuiteListener* listener);
   TestSuiteListener* unregisterTestSuiteListener(TestSuiteListener* listener);

   void registerTestCaseListener(TestCaseListener* listener);
   TestCaseListener* unregisterTestCaseListener(TestCaseListener* listener);

   void addCaseError(const TestCaseInfoReader*, const std::string&);
   void addCaseCrash(const TestCaseInfoReader*);
   void addCaseFailure(const TestCaseInfoReader*, const AssertionFailure&);
   void addCaseWarning(const TestCaseInfoReader*, const Warning&);
   void addCaseInfo(const TestCaseInfoReader*, const Info&);
   void addCaseSkipped(const TestCaseInfoReader*);

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
   SimpleTestResultDispatcherImpl *This;
};

TESTNGPP_NS_END

#endif

