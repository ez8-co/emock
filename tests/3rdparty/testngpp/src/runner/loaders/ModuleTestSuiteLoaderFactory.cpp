

#include <testngpp/internal/Error.h>
#include <testngpp/runner/loaders/ModuleTestSuiteLoaderFactory.h>
#include <testngpp/runner/loaders/ModuleTestSuiteLoader.h>
#include <testngpp/runner/loaders/ModuleLoaderFactory.h>

TESTNGPP_NS_START

/////////////////////////////////////////////////////////////////
TestSuiteLoader* 
ModuleTestSuiteLoaderFactory::create()
{
   return new ModuleTestSuiteLoader(ModuleLoaderFactory::create());
}

/////////////////////////////////////////////////////////////////

TESTNGPP_NS_END

