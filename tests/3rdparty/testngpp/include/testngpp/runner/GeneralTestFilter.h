#ifndef __TESTNGPP_GENERAL_TEST_FILTER_H
#define __TESTNGPP_GENERAL_TEST_FILTER_H

#include <testngpp/testngpp.h>
#include <testngpp/runner/TestFilter.h>

TESTNGPP_NS_START

struct NameMatcher;
struct GeneralTestFilterImpl;

////////////////////////////////////////////////////
struct GeneralTestFilter 
   : public TestFilter
{
   GeneralTestFilter(NameMatcher* fixtureMatcher, NameMatcher* caseMatcher);
   ~GeneralTestFilter();

   bool isFixtureMatch(const TestFixtureInfoReader* fixture) const;
   bool isCaseMatch(const TestCase* testcase) const;

private:
   GeneralTestFilterImpl * This;
};

////////////////////////////////////////////////////

TESTNGPP_NS_END

#endif

