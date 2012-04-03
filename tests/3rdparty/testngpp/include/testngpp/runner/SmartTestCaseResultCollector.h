
#ifndef __TESTNGPP_SMART_TESTCASE_RESULT_COLLECTOR_H
#define __TESTNGPP_SMART_TESTCASE_RESULT_COLLECTOR_H

#include <testngpp/listener/TestCaseResultCollector.h>

TESTNGPP_NS_START

struct SmartTestCaseResultCollector
      : public TestCaseResultCollector
{
   SmartTestCaseResultCollector
         ( TestCaseResultCollector*
         , bool);

   void addCaseCrash(const TestCaseInfoReader*);
   void addCaseError(const TestCaseInfoReader*, const std::string&);
   void addCaseInfo(const TestCaseInfoReader*, const TESTNGPP_NS::Info&);
   void addCaseWarning(const TestCaseInfoReader*, const TESTNGPP_NS::Warning&);
   void addCaseFailure(const TestCaseInfoReader*, const AssertionFailure&);
   void addCaseSkipped(const TestCaseInfoReader*);

   void startTestCase(const TestCaseInfoReader*);
   void endTestCase(const TestCaseInfoReader*, unsigned int, unsigned int);

private:
   bool shouldReport() const;
   void startTestCaseIfHaveNot(const TestCaseInfoReader*);

private:
   TestCaseResultCollector* collector;
   bool reportSuccess;
   bool hasFailure;
};

TESTNGPP_NS_END

#endif

