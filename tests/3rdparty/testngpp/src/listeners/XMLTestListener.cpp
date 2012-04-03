#include "XMLTestListener.h"
#include "XMLBuilder.h"

#include <fstream>
#include <iostream>

#include <testngpp/utils/Formatter.h>
#include <testngpp/utils/InternalError.h>

#include <testngpp/internal/Error.h>
#include <testngpp/internal/TestCaseInfoReader.h>
#include <testngpp/internal/TestSuiteInfoReader.h>
#include <testngpp/internal/TestFixtureInfoReader.h>

#include <testngpp/listener/TestResultReporter.h>
#include <testngpp/listener/TestSuiteResultReporter.h>
#include <testngpp/listener/TestCaseResultReporter.h>

/*
 ## doc type definition (in relaxng compact syntax)

 start = testsuites

 testsuites = element testsuites {
 testsuite*
 }

 testsuite = element testsuite {
 attribute name { text },
 attribute tests { xsd:integer },
 attribute fixtures { xsd:integer },
 attribute crashes { xsd:integer },
 attribute skips { xsd:integer },
 attribute errors { xsd:integer },
 attribute failures { xsd:integer },
 element testcase*
 }

 testcase = element testcase {
 attribute name { text },
 attribute fixture { text },
 attribute time { xsd:float },
 attribute filename { text },
 (element crash { text }
 | element error { text }
 | element failure { text })?
 }

 */

TESTNGPP_NS_START

struct XMLTestListenerImpl
{
	XMLTestListenerImpl(TestResultReporter* testResultReporter
			, TestSuiteResultReporter* testSuiteResultReporter
			, TestCaseResultReporter* testCaseResultReporter
			, std::ostream& os)
		: testResultReporter(testResultReporter)
		, testSuiteResultReporter(testSuiteResultReporter)
		, testCaseResultReporter(testCaseResultReporter)
		, os(os)
	{
		rootElement = XMLBuilder::create("testsuites");
	}

	~XMLTestListenerImpl()
	{
		delete rootElement;
	}

   ////////////////////////////////////////////////////////
	std::ostream& os;
	XMLBuilder* rootElement;
	XMLBuilder* testSuiteElement;
	XMLBuilder* testCaseElement;

   ////////////////////////////////////////////////////////
	TestResultReporter* testResultReporter;
	TestSuiteResultReporter* testSuiteResultReporter;
	TestCaseResultReporter* testCaseResultReporter;

   ////////////////////////////////////////////////////////
   void startTest();
   void endTest(unsigned int, unsigned int);
   void startTestSuite(TestSuiteInfoReader* suite);
   void endTestSuite(TestSuiteInfoReader* suite);

   void startTestCase(const TestCaseInfoReader* testcase);
   void endTestCase(const TestCaseInfoReader* testcase, unsigned int, unsigned int);
   void addCaseCrash(const TestCaseInfoReader* testcase);
   void addCaseSkipped(const TestCaseInfoReader* testcase);
   void addCaseFailure(const TestCaseInfoReader* testcase, const AssertionFailure& failure);
   void addCaseError(const TestCaseInfoReader* testcase, const std::string& msg);

	XMLBuilder&
   createTestCaseElem(const TestCaseInfoReader*);
};

///////////////////////////////////////////////////////////
void XMLTestListenerImpl::startTest()
{
}

///////////////////////////////////////////////////////////
void XMLTestListenerImpl::endTest(unsigned int, unsigned int)
{
	rootElement->write(os);
}

///////////////////////////////////////////////////////////
void XMLTestListenerImpl::
startTestSuite(TestSuiteInfoReader* suite)
{
	XMLBuilder& element = rootElement->element("testsuite");
	testSuiteElement = &element;
}

///////////////////////////////////////////////////////////
void XMLTestListenerImpl::
endTestSuite(TestSuiteInfoReader* suite)
{
	testSuiteElement->attribute("name", suite->getName())
		.attribute("tests", toValStr(testSuiteResultReporter->getNumberOfTestCases(suite)))
		.attribute("fixtures", toValStr(testSuiteResultReporter->getNumberOfFixtures(suite)))
		.attribute("crashes", toValStr(testSuiteResultReporter->getNumberOfCrashedTestCases(suite)))
		.attribute("skips",   toValStr(testSuiteResultReporter->getNumberOfSkippedTestCases(suite)))
		.attribute("errors", toValStr(testSuiteResultReporter->getNumberOfErrorTestCases(suite)))
		.attribute("failures", toValStr(testSuiteResultReporter->getNumberOfFailedTestCases(suite)));
}

///////////////////////////////////////////////////////////
XMLBuilder&
XMLTestListenerImpl::
createTestCaseElem(const TestCaseInfoReader* testcase)
{
	return testSuiteElement->element("testcase")
		.attribute("name", testcase->getName())
		.attribute("fixture", testcase->getNameOfFixture())
		.attribute("time", toValStr(0))
		.attribute("filename", testcase->getFileName());
}

///////////////////////////////////////////////////////////
void XMLTestListenerImpl::
startTestCase(const TestCaseInfoReader* testcase)
{
	testCaseElement = &(createTestCaseElem(testcase));
}

///////////////////////////////////////////////////////////
void XMLTestListenerImpl::
endTestCase(const TestCaseInfoReader* testcase, unsigned int, unsigned int)
{
}

///////////////////////////////////////////////////////////
void XMLTestListenerImpl::
addCaseCrash(const TestCaseInfoReader* testcase)
{
   testCaseElement->element("crash")
		.text("test crashed unexpectedly.");
}

///////////////////////////////////////////////////////////
void XMLTestListenerImpl::
addCaseSkipped(const TestCaseInfoReader* testcase)
{
   testCaseElement->element("skipped")
      .text("test was skipped due to the failure of its dependent case.");
}

///////////////////////////////////////////////////////////
void XMLTestListenerImpl::
addCaseError(const TestCaseInfoReader* testcase, const std::string& msg)
{
	testCaseElement->element("error")
		.text(msg);
}

///////////////////////////////////////////////////////////
void XMLTestListenerImpl::
addCaseFailure(const TestCaseInfoReader* testcase, const AssertionFailure& failure)
{
	testCaseElement->element("failure")
		.text(failure.what());
}

///////////////////////////////////////////////////////////
XMLTestListener::XMLTestListener(
        TestResultReporter* testResultReporter
		, TestSuiteResultReporter* testSuiteResultReporter
		, TestCaseResultReporter* testCaseResultReporter
		, std::ostream& os)
  : This( new XMLTestListenerImpl(testResultReporter
        , testSuiteResultReporter
        , testCaseResultReporter, os))
{
}

///////////////////////////////////////////////////////////
XMLTestListener::~XMLTestListener()
{
	delete This;
}

///////////////////////////////////////////////////////////
void XMLTestListener::
addCaseSkipped(const TestCaseInfoReader* testcase)
{
	This->addCaseSkipped(testcase);
}

///////////////////////////////////////////////////////////
void XMLTestListener::
addCaseCrash(const TestCaseInfoReader* testcase)
{
	This->addCaseCrash(testcase);
}

///////////////////////////////////////////////////////////
void XMLTestListener::
addCaseError(const TestCaseInfoReader* testcase, const std::string& msg)
{
	This->addCaseError(testcase, msg);
}

///////////////////////////////////////////////////////////
void XMLTestListener::
addCaseFailure(const TestCaseInfoReader* testcase, const AssertionFailure& failure)
{
	This->addCaseFailure(testcase, failure);
}

///////////////////////////////////////////////////////////
void XMLTestListener::
startTestCase(const TestCaseInfoReader* testcase)
{
   This->startTestCase(testcase);
}

///////////////////////////////////////////////////////////
void XMLTestListener::
endTestCase
      ( const TestCaseInfoReader* testcase
      , unsigned int secs
      , unsigned int usecs)
{
   This->endTestCase(testcase, secs, usecs);
}

///////////////////////////////////////////////////////////
void XMLTestListener::
startTestFixture(TestFixtureInfoReader* fixtureinfo)
{
}

///////////////////////////////////////////////////////////
void XMLTestListener::
endTestFixture(TestFixtureInfoReader*)
{
}

///////////////////////////////////////////////////////////
void XMLTestListener::
addFixtureError(TestFixtureInfoReader*, const std::string& msg)
{
}

///////////////////////////////////////////////////////////
void XMLTestListener::
addFixtureFailure(TestFixtureInfoReader*, const AssertionFailure& failure)
{
}

///////////////////////////////////////////////////////////
void XMLTestListener::
startTestSuite(TestSuiteInfoReader* suite)
{
   This->startTestSuite(suite);
}

///////////////////////////////////////////////////////////
void XMLTestListener::
endTestSuite(TestSuiteInfoReader* suite)
{
   This->endTestSuite(suite);
}

///////////////////////////////////////////////////////////
void XMLTestListener::
addSuiteError(TestSuiteInfoReader*, const std::string& msg)
{
}

///////////////////////////////////////////////////////////
void
XMLTestListener::
startTagsFiltering(const TagsFilterRule*)
{
}

///////////////////////////////////////////////////////////
void
XMLTestListener::
endTagsFiltering(const TagsFilterRule*)
{
}

///////////////////////////////////////////////////////////
void
XMLTestListener::
startTest()
{
   This->startTest();
}

///////////////////////////////////////////////////////////
void XMLTestListener::endTest(unsigned int secs, unsigned int usecs)
{
	This->endTest(secs, usecs);
}

///////////////////////////////////////////////////////////
void XMLTestListener::
addError(const std::string& msg)
{
}

TESTNGPP_NS_END

///////////////////////////////////////////////////////////
USING_TESTNGPP_NS

namespace
{
  std::ofstream xmlFile;
}

#define LISTENER(name) testngppxmllistener_##name

///////////////////////////////////////////////////////////
extern "C" DLL_EXPORT
TestListener* LISTENER(create_instance)(
      TestResultReporter* resultReporter
    , TestSuiteResultReporter* suiteReporter
    , TestCaseResultReporter* caseResultReporter
    , int argc, char** argv)
{
   if(argc == 1)
   {
	   return new XMLTestListener(resultReporter, suiteReporter,
			  caseResultReporter, std::cout);
   }

   xmlFile.open(argv[1]);
   return new XMLTestListener(resultReporter, suiteReporter,
			  caseResultReporter, xmlFile);
}

///////////////////////////////////////////////////////////
extern "C" DLL_EXPORT
void LISTENER(destroy_instance)(TestListener* instance)
{
   if(xmlFile.is_open()) xmlFile.close();
	delete instance;
}

///////////////////////////////////////////////////////////
