#ifndef __TESTNGPP_OR_COMPOSITE_TEST_FILTER_H
#define __TESTNGPP_OR_COMPOSITE_TEST_FILTER_H

#include <testngpp/testngpp.h>
#include <testngpp/runner/TestFilter.h>

TESTNGPP_NS_START

struct OrCompositeTestFilterImpl;

////////////////////////////////////////////////////
struct OrCompositeTestFilter 
   : public TestFilter
{
   OrCompositeTestFilter();
   ~OrCompositeTestFilter();

   void addFilter(const TestFilter* filter, bool isComposite = false);

   bool isFixtureMatch(const TestFixtureInfoReader* fixture) const;
   bool isCaseMatch(const TestCase* testcase) const;

private:
   OrCompositeTestFilterImpl * This;
};

////////////////////////////////////////////////////

TESTNGPP_NS_END

#endif

