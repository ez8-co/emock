
#ifndef __TESTNGPP_TEST_RUNNER_CONTEXT_H
#define __TESTNGPP_TEST_RUNNER_CONTEXT_H

#include <testngpp/testngpp.h>
#include <testngpp/utils/StringList.h>

TESTNGPP_NS_START

struct TestSuiteContext;
struct TestFilter;
struct TagsFilters;
struct TestResultCollector;

struct TestRunnerContextImpl;

/////////////////////////////////////////////////////////////////
struct TestRunnerContext
{
   TestRunnerContext
      ( const StringList& nameOfSuites
      , TestResultCollector* collector
      , TagsFilters* tagsFilter
      , const TestFilter* filter);

   ~TestRunnerContext();

   TestSuiteContext* getSuite(unsigned int index) const;
   unsigned int numberOfSuites() const;

private:

   TestRunnerContextImpl * This;

};

/////////////////////////////////////////////////////////////////

TESTNGPP_NS_END

#endif

