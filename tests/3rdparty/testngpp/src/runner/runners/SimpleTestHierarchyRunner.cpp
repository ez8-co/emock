
#include <iostream>

#include <testngpp/internal/TestCase.h>

#include <testngpp/listener/TestFixtureResultCollector.h>

#include <testngpp/runner/SimpleTestHierarchyRunner.h>
#include <testngpp/runner/TestHierarchyHandler.h>
#include <testngpp/runner/TestCaseRunner.h>
#include <testngpp/runner/TestCaseFilter.h>

TESTNGPP_NS_START

///////////////////////////////////////////////////////
struct SimpleTestHierarchyRunnerImpl 
{
	SimpleTestHierarchyRunnerImpl(TestCaseRunner* runner)
      : caseRunner(runner)
   {}

	void run(TestHierarchyHandler* hierarchy
      , TestFixtureResultCollector* resultCollector);

   TestCaseRunner* caseRunner; // X
};

///////////////////////////////////////////////////////
void
SimpleTestHierarchyRunnerImpl::run(TestHierarchyHandler* hierarchy
        , TestFixtureResultCollector* resultCollector)
{
   for(unsigned int i = 0; i < hierarchy->numberOfTestCasesInSched(); i++)
   {
      TestHierarchyHandler::ValueType test = hierarchy->getTestCase(i);
      TestCase* testcase = const_cast<TestCase*>(test.first);
      bool result = caseRunner->run(testcase, resultCollector, test.second);
      hierarchy->testDone(testcase, result);
   }
}

///////////////////////////////////////////////////////
SimpleTestHierarchyRunner::
SimpleTestHierarchyRunner(TestCaseRunner* caseRunner)
   : This(new SimpleTestHierarchyRunnerImpl(caseRunner))
{
}

///////////////////////////////////////////////////////
SimpleTestHierarchyRunner::~SimpleTestHierarchyRunner()
{
   delete This;
}

///////////////////////////////////////////////////////
void
SimpleTestHierarchyRunner::run(TestHierarchyHandler* hierarchy
      , TestFixtureResultCollector* resultCollector)
{
   This->run(hierarchy, resultCollector);
}

///////////////////////////////////////////////////////

TESTNGPP_NS_END

