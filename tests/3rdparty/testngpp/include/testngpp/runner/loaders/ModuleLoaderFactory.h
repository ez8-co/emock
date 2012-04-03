
#ifndef __TESTNGPP_MODULE_LOADER_FACTORY_H
#define __TESTNGPP_MODULE_LOADER_FACTORY_H

#include <testngpp/testngpp.h>


TESTNGPP_NS_START

struct ModuleLoader;

struct ModuleLoaderFactory
{
    static ModuleLoader* create();
};

TESTNGPP_NS_END

#endif

