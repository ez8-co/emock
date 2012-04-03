#ifndef __TESTNGPP_TEST_RESULT_MANAGER_H__
#define __TESTNGPP_TEST_RESULT_MANAGER_H__

#include <testngpp/testngpp.h>
#include <testngpp/utils/StringList.h>

TESTNGPP_NS_START

struct TestResultCollector;

struct TestResultManager
{
   virtual void load
         ( const StringList& searchingPaths
         , const StringList& clOfListners) = 0;

   virtual bool hasFailure() const = 0;

   virtual void startTest() = 0;
   virtual void endTest(unsigned int, unsigned int) = 0;

   virtual TestResultCollector* getResultCollector() const = 0;

   virtual ~TestResultManager() {}
};

TESTNGPP_NS_END

#endif

