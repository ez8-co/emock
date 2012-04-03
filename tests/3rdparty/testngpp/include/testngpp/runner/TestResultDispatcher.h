
#ifndef __TESTNGPP_TEST_RESULT_DISPATCHER_H
#define __TESTNGPP_TEST_RESULT_DISPATCHER_H

#include <testngpp/testngpp.h>

TESTNGPP_NS_START

struct TestListener;

struct TestResultDispatcher
{
   virtual void registerListener(TestListener* listener) = 0;
   virtual ~TestResultDispatcher() {}
};

TESTNGPP_NS_END

#endif

