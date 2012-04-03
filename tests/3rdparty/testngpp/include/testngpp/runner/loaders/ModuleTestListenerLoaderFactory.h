
#ifndef __TESTNGPP_MODULE_LISTENER_LOADER_FACTORY_H
#define __TESTNGPP_MODULE_LISTENER_LOADER_FACTORY_H

#include <testngpp/testngpp.h>

#include <testngpp/runner/loaders/TestListenerLoaderFactory.h>

TESTNGPP_NS_START

struct ModuleTestListenerLoaderFactory
   : public TestListenerLoaderFactory
{
   TestListenerLoader* create();
};

TESTNGPP_NS_END

#endif

