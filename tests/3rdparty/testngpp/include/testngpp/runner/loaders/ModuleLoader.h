
#ifndef __TESTNGPP_MODULE_LOADER_H
#define __TESTNGPP_MODULE_LOADER_H

#include <testngpp/testngpp.h>

#include <testngpp/utils/StringList.h>

TESTNGPP_NS_START

struct ModuleLoader
{
	virtual void load( const StringList& searchingPaths
                    , const std::string& modulePath) = 0;

   virtual void unload() = 0;

   virtual void* findSymbol(const std::string& symbol) = 0;

   virtual ~ModuleLoader() {}
};

TESTNGPP_NS_END

#endif

