
#ifndef __TESTNGPP_MODULE_TEST_SUITE_LOADER_H
#define __TESTNGPP_MODULE_TEST_SUITE_LOADER_H

#include <testngpp/testngpp.h>

#include <testngpp/runner/loaders/TestSuiteLoader.h>

TESTNGPP_NS_START

struct ModuleLoader;
struct TestSuiteDesc;
struct TestSuiteDescEntryNameGetter;
struct ModuleTestSuiteLoaderImpl;

struct ModuleTestSuiteLoader : public TestSuiteLoader
{
   ModuleTestSuiteLoader(ModuleLoader* loader);
   ~ModuleTestSuiteLoader();

	TestSuiteDesc*
   load( const StringList& searchingPaths
       , const std::string& path
       , TestSuiteDescEntryNameGetter* nameGetter);

   void unload();

private:
   ModuleTestSuiteLoaderImpl* This;
};

TESTNGPP_NS_END

#endif

