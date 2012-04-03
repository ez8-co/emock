
#ifndef __TESTNGPP_TEST_SUITE_LOADER_H
#define __TESTNGPP_TEST_SUITE_LOADER_H

#include <testngpp/testngpp.h>
#include <testngpp/utils/StringList.h>

TESTNGPP_NS_START

struct TestSuiteDesc;
struct TestSuiteDescEntryNameGetter;

struct TestSuiteLoader
{
   virtual TestSuiteDesc*
   load( const StringList& searchingPaths
       , const std::string& path
       , TestSuiteDescEntryNameGetter* nameGetter) = 0;

   virtual void unload() = 0;

	virtual ~TestSuiteLoader() {}
};

TESTNGPP_NS_END

#endif

