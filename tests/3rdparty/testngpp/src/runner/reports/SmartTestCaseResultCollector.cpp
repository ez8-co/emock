
#include <testngpp/runner/SmartTestCaseResultCollector.h>

TESTNGPP_NS_START

/////////////////////////////////////////////////////////////////
SmartTestCaseResultCollector::
SmartTestCaseResultCollector
      ( TestCaseResultCollector *resultCollector
      , bool shouldReportSuccess)
   : collector(resultCollector)
   , reportSuccess(shouldReportSuccess)
   , hasFailure(false)
{
}

/////////////////////////////////////////////////////////////////
bool SmartTestCaseResultCollector::
shouldReport() const
{
   return reportSuccess || hasFailure;
}

/////////////////////////////////////////////////////////////////
void SmartTestCaseResultCollector::
startTestCaseIfHaveNot(const TestCaseInfoReader* testcase)
{
   if(!shouldReport())
   {
      collector->startTestCase(testcase);
   }
}

/////////////////////////////////////////////////////////////////
void SmartTestCaseResultCollector::
addCaseCrash(const TestCaseInfoReader *testcase)
{
   startTestCaseIfHaveNot(testcase);
   collector->addCaseCrash(testcase);
   hasFailure = true;
}

/////////////////////////////////////////////////////////////////
void SmartTestCaseResultCollector::
addCaseError(const TestCaseInfoReader *testcase, const std::string & msg)
{
   startTestCaseIfHaveNot(testcase);
   collector->addCaseError(testcase, msg);
   hasFailure = true;
}

/////////////////////////////////////////////////////////////////
void SmartTestCaseResultCollector::
addCaseFailure(const TestCaseInfoReader *testcase, const AssertionFailure & failure)
{
   startTestCaseIfHaveNot(testcase);
   collector->addCaseFailure(testcase, failure);
   hasFailure = true;
}

/////////////////////////////////////////////////////////////////
void
SmartTestCaseResultCollector::
addCaseInfo(const TestCaseInfoReader *testcase, const Info & info)
{
   if(reportSuccess)
   {
      collector->addCaseInfo(testcase, info);
   }
}

/////////////////////////////////////////////////////////////////
void
SmartTestCaseResultCollector::
addCaseWarning(const TestCaseInfoReader *testcase, const Warning & warning)
{
   if(reportSuccess)
   {
      collector->addCaseWarning(testcase, warning);
   }
}

/////////////////////////////////////////////////////////////////
void
SmartTestCaseResultCollector::
addCaseSkipped(const TestCaseInfoReader *testcase)
{
   if(reportSuccess)
   {
      collector->addCaseSkipped(testcase);
   }
}

/////////////////////////////////////////////////////////////////
void
SmartTestCaseResultCollector::
startTestCase(const TestCaseInfoReader *testcase)
{
   if(shouldReport())
   {
       collector->startTestCase(testcase);
   }
}

/////////////////////////////////////////////////////////////////
void
SmartTestCaseResultCollector::
endTestCase
      ( const TestCaseInfoReader *testcase
      , unsigned int secs
      , unsigned int usecs)
{
   if(shouldReport())
   {
      collector->endTestCase(testcase, secs, usecs);
   }
}

/////////////////////////////////////////////////////////////////

TESTNGPP_NS_END
