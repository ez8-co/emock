
#include <testngpp/runner/loaders/ModuleLoader.h>
#include <testngpp/runner/loaders/ModuleLoaderFactory.h>

#include <testngpp/runner/loaders/Win32DllModuleLoader.h>


TESTNGPP_NS_START


////////////////////////////////////////////////////////
ModuleLoader*
ModuleLoaderFactory::create()
{
    return new Win32DllModuleLoader();
}

////////////////////////////////////////////////////////

TESTNGPP_NS_END

