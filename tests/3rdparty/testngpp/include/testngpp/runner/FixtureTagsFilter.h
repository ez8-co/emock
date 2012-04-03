
#ifndef __TESTNGPP_FIXTURE_TAGS_FILTER_H
#define __TESTNGPP_FIXTURE_TAGS_FILTER_H

#include <testngpp/testngpp.h>

TESTNGPP_NS_START

struct TestCase;
struct TagsFilters;
struct FixtureTagsFilterImpl;

////////////////////////////////////////////////////////
struct FixtureTagsFilter
{
   FixtureTagsFilter(TagsFilters* filter);
   ~FixtureTagsFilter();

   void startUp();

   bool shouldRun(const TestCase* testcase) const;
   bool shouldReport(const TestCase* testcase) const;
   
   bool hasSucceeded(const TestCase* testcase) const;
   bool hasFailed(const TestCase* testcase) const;
   
   void testDone(const TestCase* testcase, bool);

private:
   FixtureTagsFilterImpl* This;

};

TESTNGPP_NS_END

#endif

