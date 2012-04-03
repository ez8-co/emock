#ifndef __TESTNGPP_TEST_CASE_FILTER_H
#define __TESTNGPP_TEST_CASE_FILTER_H

#include <testngpp/testngpp.h>

TESTNGPP_NS_START

struct TestCase;

////////////////////////////////////////////////////
struct TestCaseFilter
{
   virtual bool isCaseMatch(const TestCase* testcase) const = 0;

   virtual ~TestCaseFilter() {}
};

////////////////////////////////////////////////////

TESTNGPP_NS_END

#endif

