#ifndef __TESTNGPP_TEST_FILTER_H
#define __TESTNGPP_TEST_FILTER_H

#include <testngpp/testngpp.h>
#include <testngpp/runner/TestCaseFilter.h>

TESTNGPP_NS_START

struct TestFixtureInfoReader;

////////////////////////////////////////////////////
struct TestFilter : public TestCaseFilter
{
   virtual bool isFixtureMatch(const TestFixtureInfoReader* fixture) const = 0;

   virtual ~TestFilter() {}
};

////////////////////////////////////////////////////

TESTNGPP_NS_END

#endif

