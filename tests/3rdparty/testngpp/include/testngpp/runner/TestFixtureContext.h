
#ifndef __TESTNGPP_TEST_FIXTURE_CONTEXT_H
#define __TESTNGPP_TEST_FIXTURE_CONTEXT_H

#include <testngpp/testngpp.h>

TESTNGPP_NS_START

struct TestFixtureDesc;
struct TagsFilters;
struct FixtureTagsFilter;
struct TestFixtureContextImpl;

/////////////////////////////////////////////////////////////////
struct TestFixtureContext
{
   TestFixtureContext(TestFixtureDesc* desc, TagsFilters* filters);
   ~TestFixtureContext();

   TestFixtureDesc* getFixture() const;

   FixtureTagsFilter* getTagsFilter() const;
private:

   TestFixtureContextImpl * This;

};

/////////////////////////////////////////////////////////////////

TESTNGPP_NS_END

#endif

