
#ifndef __TESTNGPP_TEST_FIXTURE_RUNNER_FACTORY_H
#define __TESTNGPP_TEST_FIXTURE_RUNNER_FACTORY_H

#include <testngpp/testngpp.h>

TESTNGPP_NS_START

struct TestFixtureRunner;

struct TestFixtureRunnerFactory
{
   static
   TestFixtureRunner* createInstance(bool useSandbox
                     , unsigned int maxConcurrent);

   static
   void destroyInstance(TestFixtureRunner* instance);

private:

   TestFixtureRunnerFactory();
};

TESTNGPP_NS_END

#endif


