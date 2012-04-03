#ifndef __TESTNGPP_WILDCARD_TEST_FILTER_H
#define __TESTNGPP_WILDCARD_TEST_FILTER_H

#include <testngpp/testngpp.h>
#include <testngpp/runner/TestFilter.h>

TESTNGPP_NS_START


////////////////////////////////////////////////////
struct WildcardTestFilter 
   : public TestFilter
{
   bool isFixtureMatch(const TestFixtureInfoReader* fixture) const;
   bool isCaseMatch(const TestCase* testcase) const;
};

////////////////////////////////////////////////////

TESTNGPP_NS_END

#endif

