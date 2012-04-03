
#include <testngpp/utils/InternalError.h>

#include <testngpp/internal/Error.h>
#include <testngpp/internal/TestCaseInfoReader.h>
#include <testngpp/internal/TestSuiteInfoReader.h>

#include <testngpp/runner/SimpleTestSuiteResultReporter.h>
#include <testngpp/runner/SimpleTestCaseResultReporter.h>


TESTNGPP_NS_START

struct SimpleTestSuiteResultReporterImpl
{
   int numberOfSuccessfulCases;
   int numberOfCrashedCases;
   int numberOfSkippedCases;
   int numberOfErrorCases;
   int numberOfFailedCases;

   int numberOfFixtures;
   int numberOfFixtureErrors;
   int numberOfFixtureFailures;

   int numberOfSuiteErrors;

   int getNumberOfUnsuccessfulCases() const;
   int getNumberOfTestCases() const;

   bool readable(TestSuiteInfoReader* suite) const;
   bool isThatMe(TestSuiteInfoReader* suite) const;

   SimpleTestSuiteResultReporterImpl(
        TestCaseResultReporter* caseReporter)
      : numberOfCrashedCases(0)
      , numberOfErrorCases(0)
      , numberOfFailedCases(0)
      , numberOfSuccessfulCases(0)
      , numberOfFixtureErrors(0)
      , numberOfFixtureFailures(0)
      , numberOfSuiteErrors(0)
      , currentSuite(0)
      , caseResultReporter(caseReporter)
   {}

   TestFixtureInfoReader* currentFixture;
   TestSuiteInfoReader* currentSuite;
   TestCaseResultReporter* caseResultReporter;

   bool finished;
};

///////////////////////////////////////////////////////////
bool
SimpleTestSuiteResultReporterImpl::
readable(TestSuiteInfoReader* suite) const
{
   return isThatMe(suite) && finished;
}

///////////////////////////////////////////////////////////
bool
SimpleTestSuiteResultReporterImpl::
isThatMe(TestSuiteInfoReader* suite) const
{
   return suite != 0 && suite == currentSuite;
}

///////////////////////////////////////////////////////////
int
SimpleTestSuiteResultReporterImpl::
getNumberOfUnsuccessfulCases() const
{
   return numberOfCrashedCases + numberOfErrorCases + numberOfFailedCases + numberOfSkippedCases;
}

///////////////////////////////////////////////////////////
int
SimpleTestSuiteResultReporterImpl::getNumberOfTestCases() const
{
   return getNumberOfUnsuccessfulCases() + numberOfSuccessfulCases;
}

///////////////////////////////////////////////////////////
SimpleTestSuiteResultReporter::
SimpleTestSuiteResultReporter(TestCaseResultReporter* caseResultReporter)
   : This(new SimpleTestSuiteResultReporterImpl(caseResultReporter))
{
}

///////////////////////////////////////////////////////////
SimpleTestSuiteResultReporter::~SimpleTestSuiteResultReporter()
{
   delete This;
}

///////////////////////////////////////////////////////////
void SimpleTestSuiteResultReporter::
addCaseCrash(const TestCaseInfoReader* testcase)
{
}

///////////////////////////////////////////////////////////
void SimpleTestSuiteResultReporter::
addCaseSkipped(const TestCaseInfoReader* testcase)
{
}

///////////////////////////////////////////////////////////
void SimpleTestSuiteResultReporter::
addCaseError(const TestCaseInfoReader* testcase, const std::string& msg)
{
}

///////////////////////////////////////////////////////////
void SimpleTestSuiteResultReporter::
addCaseFailure(const TestCaseInfoReader* testcase, const AssertionFailure& failure)
{
}

///////////////////////////////////////////////////////////
void SimpleTestSuiteResultReporter::
startTestCase(const TestCaseInfoReader*)
{
}

///////////////////////////////////////////////////////////
void SimpleTestSuiteResultReporter::
endTestCase(const TestCaseInfoReader* testcase, unsigned int, unsigned int)
{
   switch(This->caseResultReporter->getTestCaseResult(testcase))
   {
   case TestCaseResultReporter::TR_SUCCESS:
      This->numberOfSuccessfulCases++;
      break;
   case TestCaseResultReporter::TR_FAILED:
      This->numberOfFailedCases++;
      break;
   case TestCaseResultReporter::TR_ERROR:
      This->numberOfErrorCases++;
      break;
   case TestCaseResultReporter::TR_CRASHED:
      This->numberOfCrashedCases++;
      break;
   case TestCaseResultReporter::TR_SKIPPED:
      This->numberOfSkippedCases++;
      break;
   case TestCaseResultReporter::TR_UNKNOWN:
   default:
      throw Error(TESTNGPP_INTERNAL_ERROR(6003));
   }
}

///////////////////////////////////////////////////////////
void SimpleTestSuiteResultReporter::
startTestFixture(TestFixtureInfoReader* fixture)
{
   This->currentFixture = fixture;
}

///////////////////////////////////////////////////////////
void SimpleTestSuiteResultReporter::
endTestFixture(TestFixtureInfoReader* fixture)
{
   if(This->currentFixture != fixture)
   {
      TESTNGPP_INTERNAL_ERROR(2019);
   }

   This->numberOfFixtures++;
}

///////////////////////////////////////////////////////////
void SimpleTestSuiteResultReporter::
addFixtureError(TestFixtureInfoReader*, const std::string& msg)
{
   This->numberOfFixtureErrors++;
}

///////////////////////////////////////////////////////////
void SimpleTestSuiteResultReporter::
addFixtureFailure(TestFixtureInfoReader* suite, const AssertionFailure& failure)
{
   This->numberOfFixtureFailures++;
}

///////////////////////////////////////////////////////////
void SimpleTestSuiteResultReporter::
startTestSuite(TestSuiteInfoReader* suite)
{
   if(This->currentSuite != 0 && (!This->finished))
   {
      throw Error(TESTNGPP_INTERNAL_ERROR(6001));
   }

   This->currentSuite = suite;
   This->finished = false;

   This->numberOfSuccessfulCases = 0;
   This->numberOfCrashedCases = 0;
   This->numberOfSkippedCases = 0;
   This->numberOfErrorCases = 0;
   This->numberOfFailedCases = 0;

   This->numberOfFixtures = 0;
   This->numberOfFixtureErrors = 0;
   This->numberOfFixtureFailures = 0;
   This->numberOfSuiteErrors = 0;
}

///////////////////////////////////////////////////////////
void SimpleTestSuiteResultReporter::
endTestSuite(TestSuiteInfoReader* suite)
{
   if(This->isThatMe(suite))   
   {
      This->finished = true;
   }
}

///////////////////////////////////////////////////////////
void SimpleTestSuiteResultReporter::
addSuiteError(TestSuiteInfoReader* suite, const std::string& msg)
{
   if(!This->isThatMe(suite)) 
   {
      throw Error(TESTNGPP_INTERNAL_ERROR(6002));
   }

   This->numberOfSuiteErrors++;
}

///////////////////////////////////////////////////////////
int
SimpleTestSuiteResultReporter::
getNumberOfTestCases(TestSuiteInfoReader* suite) const
{
   if(This->readable(suite))
   {
      return This->getNumberOfTestCases();
   }

   return -1;
}

///////////////////////////////////////////////////////////
int
SimpleTestSuiteResultReporter::
getNumberOfSuccessfulTestCases(TestSuiteInfoReader* suite) const
{
   if(This->readable(suite))
   {
      return This->numberOfSuccessfulCases;
   }

   return -1;
}

///////////////////////////////////////////////////////////
int
SimpleTestSuiteResultReporter::
getNumberOfUnsuccessfulTestCases(TestSuiteInfoReader* suite) const
{
   if(This->readable(suite))
   {
      return This->getNumberOfUnsuccessfulCases(); 
   }

   return -1;
}

///////////////////////////////////////////////////////////
int
SimpleTestSuiteResultReporter::
getNumberOfFailedTestCases(TestSuiteInfoReader* suite) const
{
   if(This->readable(suite))
   {
      return This->numberOfFailedCases;
   }

   return -1;
}

///////////////////////////////////////////////////////////
int
SimpleTestSuiteResultReporter::
getNumberOfErrorTestCases(TestSuiteInfoReader* suite) const
{
   if(This->readable(suite))
   {
      return This->numberOfErrorCases;
   }

   return -1;
}

///////////////////////////////////////////////////////////
int
SimpleTestSuiteResultReporter::
getNumberOfCrashedTestCases(TestSuiteInfoReader* suite) const
{
   if(This->readable(suite))
   {
      return This->numberOfCrashedCases;
   }

   return -1;
}

///////////////////////////////////////////////////////////
int
SimpleTestSuiteResultReporter::
getNumberOfFixtureErrors(TestSuiteInfoReader* suite) const
{
   if(This->readable(suite))
   {
      return This->numberOfFixtureErrors;
   }

   return -1;
}

///////////////////////////////////////////////////////////
int
SimpleTestSuiteResultReporter::
getNumberOfFixtureFailures(TestSuiteInfoReader* suite) const
{
   if(This->readable(suite))
   {
      return This->numberOfFixtureFailures;
   }

   return -1;
}

///////////////////////////////////////////////////////////
int
SimpleTestSuiteResultReporter::
getNumberOfSuiteErrors(TestSuiteInfoReader* suite) const
{
   if(This->readable(suite))
   {
      return This->numberOfSuiteErrors;
   }

   return -1;
}

///////////////////////////////////////////////////////////
int
SimpleTestSuiteResultReporter::
getNumberOfSkippedTestCases(TestSuiteInfoReader* suite) const
{
   if(This->readable(suite))
   {
      return This->numberOfSkippedCases;
   }

   return -1;
}
///////////////////////////////////////////////////////////
int
SimpleTestSuiteResultReporter::
getNumberOfFixtures(TestSuiteInfoReader* suite) const
{
   if(This->readable(suite))
   {
      return This->numberOfFixtures;
   }

   return -1;
}
///////////////////////////////////////////////////////////

TESTNGPP_NS_END
