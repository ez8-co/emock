
#ifndef __TESTNGPP_TEST_SUITE_DESC_ENTRY_NAME_GETTER_H
#define __TESTNGPP_TEST_SUITE_DESC_ENTRY_NAME_GETTER_H

#include <string>

#include <testngpp/testngpp.h>

TESTNGPP_NS_START

struct TestSuiteDescEntryNameGetter
{
	virtual std::string getDescEntryName() const = 0;
   virtual ~TestSuiteDescEntryNameGetter() {}
};

TESTNGPP_NS_END

#endif

