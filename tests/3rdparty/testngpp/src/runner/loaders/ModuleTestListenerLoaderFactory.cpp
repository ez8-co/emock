
#include <testngpp/runner/loaders/ModuleTestListenerLoaderFactory.h>
#include <testngpp/runner/loaders/ModuleTestListenerLoader.h>
#include <testngpp/runner/loaders/ModuleLoaderFactory.h>

TESTNGPP_NS_START

/////////////////////////////////////////////////////////////////
TestListenerLoader* 
ModuleTestListenerLoaderFactory::create()
{
   return new ModuleTestListenerLoader(ModuleLoaderFactory::create());
}

/////////////////////////////////////////////////////////////////

TESTNGPP_NS_END

