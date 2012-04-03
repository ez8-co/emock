
#ifndef __TESTNGPP_TEST_CASE_RESULT_DISPATCHER_H
#define __TESTNGPP_TEST_CASE_RESULT_DISPATCHER_H

#include <testngpp/testngpp.h>

TESTNGPP_NS_START

struct TestCaseListener;

struct TestCaseResultDispatcher
{
   virtual void registerTestCaseListener(TestCaseListener* listener) = 0;
   virtual TestCaseListener* unregisterTestCaseListener(TestCaseListener* listener) = 0;

   virtual ~TestCaseResultDispatcher() {}
};

TESTNGPP_NS_END

#endif

