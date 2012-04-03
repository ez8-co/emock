
#ifndef __TESTNGPP_TEST_SUITE_RESULT_DISPATCHER_H
#define __TESTNGPP_TEST_SUITE_RESULT_DISPATCHER_H

#include <testngpp/testngpp.h>

TESTNGPP_NS_START

struct TestSuiteListener;

struct TestSuiteResultDispatcher
{
   virtual void registerTestSuiteListener(TestSuiteListener* listener) = 0;
   virtual TestSuiteListener* unregisterTestSuiteListener(TestSuiteListener* listener) = 0;

   virtual ~TestSuiteResultDispatcher() {}
};

TESTNGPP_NS_END

#endif

