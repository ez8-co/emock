#ifndef __TESTNGPP_TEST_FILTER_FACTORY_H
#define __TESTNGPP_TEST_FILTER_FACTORY_H

#include <testngpp/testngpp.h>
#include <testngpp/utils/StringList.h>

TESTNGPP_NS_START

struct TestFilter;

////////////////////////////////////////////////////
struct TestFilterFactory
{
   static const TestFilter* getFilter(const StringList& filterOptions);
   static void returnFilter(const TestFilter* filter);
};

////////////////////////////////////////////////////

TESTNGPP_NS_END

#endif

