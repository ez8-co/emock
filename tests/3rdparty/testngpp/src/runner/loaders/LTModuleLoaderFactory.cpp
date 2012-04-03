
#include <testngpp/runner/ModuleLoader.h>
#include <testngpp/runner/ModuleLoaderFactory.h>

#include <testngpp/runner/LTModuleLoader.h>

TESTNGPP_NS_START


////////////////////////////////////////////////////////
ModuleLoader*
ModuleLoaderFactory::create()
{
    return new LTModuleLoader();
}

////////////////////////////////////////////////////////

TESTNGPP_NS_END

