
#ifndef __TESTNGPP_TEST_SUITE_LOADER_FACTORY_H
#define __TESTNGPP_TEST_SUITE_LOADER_FACTORY_H

#include <testngpp/testngpp.h>

TESTNGPP_NS_START

struct TestSuiteLoader;

struct TestSuiteLoaderFactory
{
   virtual TestSuiteLoader* create() = 0;

	virtual ~TestSuiteLoaderFactory() {}
};

TESTNGPP_NS_END

#endif

