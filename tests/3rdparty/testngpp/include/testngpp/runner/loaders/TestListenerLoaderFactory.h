
#ifndef __TESTNGPP_TEST_LISTENER_LOADER_FACTORY_H
#define __TESTNGPP_TEST_LISTENER_LOADER_FACTORY_H

#include <testngpp/testngpp.h>

TESTNGPP_NS_START

struct TestListenerLoader;
struct TestResultReporter;
struct TestSuiteResultReporter;
struct TestCaseResultReporter;

struct TestListenerLoaderFactory
{
   virtual TestListenerLoader* create() = 0;

	virtual ~TestListenerLoaderFactory() {}
};

TESTNGPP_NS_END

#endif

