
#ifndef __TESTNGPP_MODULE_TEST_LISTENER_LOADER_H
#define __TESTNGPP_MODULE_TEST_LISTENER_LOADER_H

#include <list>

#include <testngpp/testngpp.h>

#include <testngpp/runner/loaders/TestListenerLoader.h>

TESTNGPP_NS_START

struct ModuleLoader;
struct ModuleTestListenerLoaderImpl;

struct ModuleTestListenerLoader : public TestListenerLoader
{
   ModuleTestListenerLoader(ModuleLoader* loader);
   ~ModuleTestListenerLoader();

   TestListener*
   load( const StringList& SearchingPaths
       , const std::string& commandLine
       , TestResultReporter* resultReporter
       , TestSuiteResultReporter* suiteResultReporter
       , TestCaseResultReporter* caseResultReporter);

private:

   ModuleTestListenerLoaderImpl* This;

};

TESTNGPP_NS_END

#endif

