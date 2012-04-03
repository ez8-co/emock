
#ifndef __TESTNGPP_TEST_SUITE_LISTENER_H
#define __TESTNGPP_TEST_SUITE_LISTENER_H

#include <testngpp/testngpp.h>

#include <testngpp/listener/TestSuiteResultCollector.h>

TESTNGPP_NS_START

struct TestSuiteListener
   : public TestSuiteResultCollector
{
   virtual ~TestSuiteListener() {}
};

TESTNGPP_NS_END

#endif

