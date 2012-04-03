
#ifndef __TESTNGPP_LT_MODULE_LOADER_H
#define __TESTNGPP_LT_MODULE_LOADER_H

#include <testngpp/testngpp.h>
#include <testngpp/runner/loaders/ModuleLoader.h>
#include <testngpp/runner/SearchingPaths.h>


TESTNGPP_NS_START

struct LTModuleLoaderImpl;

struct LTModuleLoader : public ModuleLoader
{
   LTModuleLoader(const SearchingPaths* searchingPaths);

   ~LTModuleLoader(); 

	void load(const std::string& modulePath);

   void unload();

   void* findSymbol(const std::string& symbol);

private:

   LTModuleLoaderImpl* This;
};

TESTNGPP_NS_END

#endif

