
#include <iostream>

#include <testngpp/internal/Error.h>
#include <testngpp/utils/InternalError.h>

#include <testngpp/runner/SimpleTestCaseResultReporter.h>

TESTNGPP_NS_START

struct SimpleTestCaseResultReporterImpl
{
   TestCaseInfoReader* testcase;
   bool informedError;
   bool informedFailure;
   bool informedCrashed;
   bool informedSkipped;
   bool finished;

   SimpleTestCaseResultReporterImpl()
      : testcase(0)
      , informedError(false)
      , informedFailure(false)
      , informedCrashed(false)
      , informedSkipped(false)
      , finished(false)
   {}
};

///////////////////////////////////////////////////////////
SimpleTestCaseResultReporter::
SimpleTestCaseResultReporter()
   : This(new SimpleTestCaseResultReporterImpl())
{
}

///////////////////////////////////////////////////////////
SimpleTestCaseResultReporter::
~SimpleTestCaseResultReporter()
{
   delete This;
}

///////////////////////////////////////////////////////////
unsigned int
SimpleTestCaseResultReporter::
getTestCaseResult(const TestCaseInfoReader* testcase) const
{
   if(testcase == This->testcase && This->finished) 
   {
      if(This->informedCrashed) return TestCaseResultReporter::TR_CRASHED;
      if(This->informedError) return TestCaseResultReporter::TR_ERROR;
      if(This->informedFailure) return TestCaseResultReporter::TR_FAILED;
      if(This->informedSkipped) return TestCaseResultReporter::TR_SKIPPED;

      return TestCaseResultReporter::TR_SUCCESS;
   }

   return TestCaseResultReporter::TR_UNKNOWN;
}

///////////////////////////////////////////////////////////
void SimpleTestCaseResultReporter::
addCaseSkipped(const TestCaseInfoReader* testcase)
{
   if(This->testcase != testcase)
   {
      return;
   }

   This->finished = true;
   This->informedSkipped = true;
}

///////////////////////////////////////////////////////////
void SimpleTestCaseResultReporter::
addCaseCrash(const TestCaseInfoReader* testcase)
{
   if(This->testcase != testcase)
   {
      return;
   }

   This->finished = true;
   This->informedCrashed = true;
}

///////////////////////////////////////////////////////////
void SimpleTestCaseResultReporter::
addCaseError(const TestCaseInfoReader* testcase, const std::string& msg)
{
   if(This->testcase != testcase)
   {
      return;
   }

   This->informedError = true;
}

///////////////////////////////////////////////////////////
void SimpleTestCaseResultReporter::
addCaseFailure(const TestCaseInfoReader* testcase, const AssertionFailure& failure)
{
   if(This->testcase != testcase)
   {
      return;
   }

   This->informedFailure = true;
}

///////////////////////////////////////////////////////////
void SimpleTestCaseResultReporter::
startTestCase(const TestCaseInfoReader* testcase)
{
   if(This->testcase != 0 && !This->finished)
   {
      throw Error(TESTNGPP_INTERNAL_ERROR(2001));
   }

   This->testcase = const_cast<TestCaseInfoReader*>(testcase);
   This->informedError = false;
   This->informedFailure = false;
   This->informedCrashed = false;
   This->finished = false;
   This->informedSkipped = false;
}

///////////////////////////////////////////////////////////
void SimpleTestCaseResultReporter::
endTestCase
      ( const TestCaseInfoReader* testcase
      , unsigned int
      , unsigned int)
{
   if(This->testcase != testcase)
   {
      return;
   }

   This->finished = true;
}

///////////////////////////////////////////////////////////

TESTNGPP_NS_END
