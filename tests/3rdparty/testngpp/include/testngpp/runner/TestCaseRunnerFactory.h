
#ifndef __TESTNGPP_TESTCASE_RUNNER_FACTORY_H
#define __TESTNGPP_TESTCASE_RUNNER_FACTORY_H

#include <testngpp/testngpp.h>

TESTNGPP_NS_START

struct TestCaseRunner;

struct TestCaseRunnerFactory
{
   static TestCaseRunner* createInstance();
   static void releaseInstance(TestCaseRunner* runner);
};

TESTNGPP_NS_END

#endif
