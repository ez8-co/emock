
#include <iostream>
#include <testngpp/internal/TestCaseInfoReader.h>
#include <testngpp/internal/TestSuiteInfoReader.h>

#include <testngpp/listener/TestSuiteResultReporter.h>

#include <testngpp/runner/SimpleTestResultReporter.h>

TESTNGPP_NS_START

struct SimpleTestResultReporterImpl
{
   unsigned int numberOfSuccessfulCases;
   unsigned int numberOfCrashedCases;
   unsigned int numberOfSkippedCases;
   unsigned int numberOfErrorCases;
   unsigned int numberOfFailedCases;
   unsigned int numberOfLoadedSuites;
   unsigned int numberOfUnloadableSuites;
   unsigned int numberOfErrorFixtures;
   
   TestSuiteResultReporter* suiteResultReporter;

   unsigned int getNumberOfUnsuccessfulCases() const;
   unsigned int getNumberOfTestCases() const;

   unsigned int round;

   SimpleTestResultReporterImpl(TestSuiteResultReporter* suiteReporter)
      : numberOfCrashedCases(0)
      , numberOfSkippedCases(0)
      , numberOfErrorCases(0)
      , numberOfFailedCases(0)
      , numberOfSuccessfulCases(0)
      , numberOfLoadedSuites(0)
      , numberOfUnloadableSuites(0)
      , numberOfErrorFixtures(0)
      , suiteResultReporter(suiteReporter)
      , round(0)
   {}
};

///////////////////////////////////////////////////////////
unsigned int
SimpleTestResultReporterImpl::
getNumberOfUnsuccessfulCases() const
{
   return numberOfCrashedCases + numberOfErrorCases + numberOfFailedCases + numberOfSkippedCases;
}

///////////////////////////////////////////////////////////
unsigned int
SimpleTestResultReporterImpl::getNumberOfTestCases() const
{
   return getNumberOfUnsuccessfulCases() + numberOfSuccessfulCases;
}
///////////////////////////////////////////////////////////
SimpleTestResultReporter::
SimpleTestResultReporter(TestSuiteResultReporter* suiteResultReporter)
   : This(new SimpleTestResultReporterImpl(suiteResultReporter))
{
}

///////////////////////////////////////////////////////////
SimpleTestResultReporter::~SimpleTestResultReporter()
{
   delete This;
}

///////////////////////////////////////////////////////////
void SimpleTestResultReporter::
addCaseCrash(const TestCaseInfoReader* testcase)
{
}

///////////////////////////////////////////////////////////
void SimpleTestResultReporter::
addCaseSkipped(const TestCaseInfoReader* testcase)
{
}

///////////////////////////////////////////////////////////
void SimpleTestResultReporter::
addCaseError(const TestCaseInfoReader* testcase, const std::string& msg)
{
}

///////////////////////////////////////////////////////////
void SimpleTestResultReporter::
addCaseFailure(const TestCaseInfoReader* testcase, const AssertionFailure& failure)
{
}

///////////////////////////////////////////////////////////
void SimpleTestResultReporter::
startTestCase(const TestCaseInfoReader*)
{
}

///////////////////////////////////////////////////////////
void SimpleTestResultReporter::
endTestCase(const TestCaseInfoReader*, unsigned int, unsigned int)
{
}

///////////////////////////////////////////////////////////
void SimpleTestResultReporter::
startTestFixture(TestFixtureInfoReader*)
{
}

///////////////////////////////////////////////////////////
void SimpleTestResultReporter::
endTestFixture(TestFixtureInfoReader*)
{
}

///////////////////////////////////////////////////////////
void SimpleTestResultReporter::
addFixtureError(TestFixtureInfoReader*, const std::string& msg)
{
    This->numberOfErrorFixtures++;
}

///////////////////////////////////////////////////////////
void SimpleTestResultReporter::
addFixtureFailure(TestFixtureInfoReader*, const AssertionFailure& failure)
{
}

///////////////////////////////////////////////////////////
void SimpleTestResultReporter::
startTestSuite(TestSuiteInfoReader* suite)
{
   if(This->round == 1) This->numberOfLoadedSuites++;
}

///////////////////////////////////////////////////////////
void SimpleTestResultReporter::
endTestSuite(TestSuiteInfoReader* suite)
{
   This->numberOfSuccessfulCases += \
          This->suiteResultReporter->getNumberOfSuccessfulTestCases(suite);

   This->numberOfCrashedCases += \
          This->suiteResultReporter->getNumberOfCrashedTestCases(suite);

   This->numberOfErrorCases += \
          This->suiteResultReporter->getNumberOfErrorTestCases(suite);

   This->numberOfFailedCases += \
          This->suiteResultReporter->getNumberOfFailedTestCases(suite);

   This->numberOfSkippedCases += \
          This->suiteResultReporter->getNumberOfSkippedTestCases(suite);
}

///////////////////////////////////////////////////////////
void SimpleTestResultReporter::
addSuiteError(TestSuiteInfoReader*, const std::string& msg )
{
}

///////////////////////////////////////////////////////////
void SimpleTestResultReporter::
startTagsFiltering(const TagsFilterRule*)
{
   This->round++;
}

///////////////////////////////////////////////////////////
void SimpleTestResultReporter::
endTagsFiltering(const TagsFilterRule*)
{
}

///////////////////////////////////////////////////////////
void SimpleTestResultReporter::
startTest()
{
}

///////////////////////////////////////////////////////////
void SimpleTestResultReporter::
endTest(unsigned int, unsigned int)
{
}

///////////////////////////////////////////////////////////
void SimpleTestResultReporter::
addError(const std::string& msg)
{
   This->numberOfUnloadableSuites++;
}

///////////////////////////////////////////////////////////
unsigned int
SimpleTestResultReporter::
getNumberOfTestCases() const
{
   return This->getNumberOfTestCases();
}

///////////////////////////////////////////////////////////
unsigned int
SimpleTestResultReporter::
getNumberOfSuccessfulTestCases() const
{
   return This->numberOfSuccessfulCases;
}

///////////////////////////////////////////////////////////
unsigned int
SimpleTestResultReporter::
getNumberOfUnsuccessfulTestCases() const
{
   return This->getNumberOfUnsuccessfulCases(); 
}

///////////////////////////////////////////////////////////
unsigned int
SimpleTestResultReporter::
getNumberOfFailedTestCases() const
{
   return This->numberOfFailedCases;
}

///////////////////////////////////////////////////////////
unsigned int
SimpleTestResultReporter::
getNumberOfErrorTestCases() const
{
   return This->numberOfErrorCases;
}

///////////////////////////////////////////////////////////
unsigned int
SimpleTestResultReporter::
getNumberOfSkippedTestCases() const
{
   return This->numberOfSkippedCases;
}

///////////////////////////////////////////////////////////
unsigned int
SimpleTestResultReporter::
getNumberOfCrashedTestCases() const
{
   return This->numberOfCrashedCases;
}

///////////////////////////////////////////////////////////
unsigned int
SimpleTestResultReporter::
getNumberOfUnloadableSuites() const
{
   return This->numberOfUnloadableSuites;
}

unsigned int
SimpleTestResultReporter::
getNumberOfLoadedSuites() const
{
   return This->numberOfLoadedSuites;
}

unsigned int
SimpleTestResultReporter::
getNumberOfErrorFixtures() const
{
   return This->numberOfErrorFixtures;
}


///////////////////////////////////////////////////////////

TESTNGPP_NS_END
