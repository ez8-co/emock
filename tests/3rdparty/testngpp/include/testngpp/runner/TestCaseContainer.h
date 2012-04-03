
#ifndef __TESTNGPP_TESTCASE_CONTAINER_H
#define __TESTNGPP_TESTCASE_CONTAINER_H

#include <testngpp/testngpp.h>

TESTNGPP_NS_START

struct TestCase;

struct TestCaseContainer
{
   virtual void
   addTestCase( const TestCase* testcase
              , bool useSpecified) = 0;

   virtual ~TestCaseContainer() {}
};

TESTNGPP_NS_END

#endif

