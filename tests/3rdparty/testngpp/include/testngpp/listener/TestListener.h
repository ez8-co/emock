
#ifndef __TESTNGPP_TEST_LISTENER_H
#define __TESTNGPP_TEST_LISTENER_H

#include <testngpp/testngpp.h>

#include <testngpp/listener/TestResultCollector.h>

TESTNGPP_NS_START

struct TestListener
   : public TestResultCollector
{
   virtual ~TestListener() {}
};

TESTNGPP_NS_END

#endif

