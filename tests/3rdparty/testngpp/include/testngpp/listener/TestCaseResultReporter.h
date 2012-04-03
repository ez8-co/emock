
#ifndef __TESTNGPP_TEST_CASE_RESULT_REPORTER_H
#define __TESTNGPP_TEST_CASE_RESULT_REPORTER_H

#include <testngpp/testngpp.h>

TESTNGPP_NS_START

struct TestCaseInfoReader;

struct TestCaseResultReporter
{
   enum {
      TR_SUCCESS = 0,
      TR_FAILED  = 1,
      TR_ERROR   = 2,
      TR_CRASHED = 3,
      TR_SKIPPED = 4,
      TR_UNKNOWN = 5
   };
   
   virtual unsigned int getTestCaseResult(const TestCaseInfoReader*) const = 0;

   virtual ~TestCaseResultReporter() {}
};

TESTNGPP_NS_END

#endif

