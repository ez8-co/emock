
#ifndef __TESTNGPP_TEST_CASE_LISTENER_H
#define __TESTNGPP_TEST_CASE_LISTENER_H

#include <testngpp/testngpp.h>

#include <testngpp/listener/TestCaseResultCollector.h>

TESTNGPP_NS_START

struct TestCaseListener
   : public TestCaseResultCollector
{
   virtual ~TestCaseListener() {}
};

TESTNGPP_NS_END

#endif

