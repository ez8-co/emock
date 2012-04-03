
#ifndef __TESTNGPP_MODULE_SUITE_LOADER_FACTORY_H
#define __TESTNGPP_MODULE_SUITE_LOADER_FACTORY_H

#include <testngpp/testngpp.h>

#include <testngpp/runner/loaders/TestSuiteLoaderFactory.h>

TESTNGPP_NS_START

struct ModuleTestSuiteLoaderFactory
   : public TestSuiteLoaderFactory
{
   TestSuiteLoader* create();
};

TESTNGPP_NS_END

#endif

