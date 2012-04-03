
#include <testngpp/runner/loaders/ModuleLoader.h>
#include <testngpp/runner/loaders/ModuleLoaderFactory.h>

#include <testngpp/runner/loaders/DLModuleLoader.h>

TESTNGPP_NS_START


////////////////////////////////////////////////////////
ModuleLoader*
ModuleLoaderFactory::create()
{
    return new DLModuleLoader();
}

////////////////////////////////////////////////////////

TESTNGPP_NS_END

