
#ifndef __TESTNGPP_TEST_CASE_RESULT_COLLECTOR_H
#define __TESTNGPP_TEST_CASE_RESULT_COLLECTOR_H

#include <string>

#include <testngpp/testngpp.h>
#include <testngpp/internal/AssertionFailure.h>
#include <testngpp/internal/Warning.h>
#include <testngpp/internal/Info.h>

TESTNGPP_NS_START

struct AssertionFailure;
struct TestCaseInfoReader;

struct TestCaseResultCollector
{
   virtual void addCaseCrash(const TestCaseInfoReader*) {}
   virtual void addCaseError(const TestCaseInfoReader*, const std::string&) {}
   virtual void addCaseInfo(const TestCaseInfoReader*, const TESTNGPP_NS::Info&) {}
   virtual void addCaseWarning(const TestCaseInfoReader*, const TESTNGPP_NS::Warning&) {}
	virtual void addCaseFailure(const TestCaseInfoReader*, const AssertionFailure&)  {}
	virtual void addCaseSkipped(const TestCaseInfoReader*)  {}

   virtual void startTestCase
                  ( const TestCaseInfoReader* ) {}

   virtual void endTestCase
                  ( const TestCaseInfoReader*
                  , unsigned int secs
                  , unsigned int uSecs) = 0;

	virtual ~TestCaseResultCollector() {}
};

TESTNGPP_NS_END

#endif

