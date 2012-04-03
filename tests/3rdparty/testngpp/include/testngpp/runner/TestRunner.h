#ifndef __TESTNGPP_TEST_RUNNER_H
#define __TESTNGPP_TEST_RUNNER_H

#include <string>

#include <testngpp/testngpp.h>

#include <testngpp/utils/StringList.h>

TESTNGPP_NS_START

struct TestRunnerImpl;

struct TestRunner
{
public:
   TestRunner();
   ~TestRunner();

   int runTests( bool useSandboxRunner
               , unsigned int maxConcurrent
               , const StringList& suitePaths
               , const StringList& listenerNames
               , const StringList& searchingPathsOfListeners
               , const StringList& fixtures
               , const std::string& tagsFilterOption);

private:
   TestRunnerImpl * This;

};

TESTNGPP_NS_END

#endif

