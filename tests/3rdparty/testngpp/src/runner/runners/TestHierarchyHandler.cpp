
#include <utility>
#include <list>

#include <testngpp/utils/InternalError.h>

#include <testngpp/internal/TestCase.h>
#include <testngpp/internal/TestFixtureDesc.h>

#include <testngpp/listener/TestFixtureResultCollector.h>

#include <testngpp/runner/TestCaseHierarchy.h>
#include <testngpp/runner/TestCaseContainer.h>
#include <testngpp/runner/TestHierarchyHandler.h>
#include <testngpp/runner/TestCaseFilter.h>
#include <testngpp/runner/FixtureTagsFilter.h>

TESTNGPP_NS_START

namespace
{

struct SkippedTestCases
   : public TestCaseContainer
{
   SkippedTestCases
         ( TestFixtureResultCollector* resultCollector
         , FixtureTagsFilter* filter)
         : collector(resultCollector)
         , tagsFilter(filter)
   {
   }

   void addTestCase
         ( const TestCase* testcase
         , bool userSpecified)
   {
      tagsFilter->testDone(testcase, false);
  
      if(!userSpecified)
         return;
      
      collector->startTestCase(testcase);
      collector->addCaseSkipped(testcase);
      collector->endTestCase(testcase, 0, 0);
   }

private:
   TestFixtureResultCollector* collector;
   FixtureTagsFilter* tagsFilter;
};

   
struct ComplexTestCaseFilter 
      : public TestCaseFilter
{
   ComplexTestCaseFilter
      ( FixtureTagsFilter* fixtureTagsFilter
      , const TestCaseFilter* filter)
      : fnMatcher(filter)
      , tagsFilter(fixtureTagsFilter)
   { }
   
   bool isCaseMatch(const TestCase* testcase) const
   {
      return fnMatcher->isCaseMatch(testcase) && \
             tagsFilter->shouldRun(testcase);
   }
   
private:
   const TestCaseFilter* fnMatcher;
   FixtureTagsFilter* tagsFilter;
};

}
   
///////////////////////////////////////////////////
struct TestHierarchyHandlerImpl
   : public TestCaseContainer
{
   typedef TestHierarchyHandler::ValueType ValueType;
   
   TestHierarchyHandlerImpl
	   ( const std::string&
	   , TestFixtureDesc* fixture 
       , const TestCaseFilter* filter
       , FixtureTagsFilter* tagsFilter
       , TestFixtureResultCollector* collector);

   ~TestHierarchyHandlerImpl();

   void addTestCase
         ( const TestCase* testcase
         , bool userSpecified);

   void testDone
         ( const TestCase* testcase
         , bool hasSucceeded);

   bool shouldReport(const TestCase* testcase) const;
   
   unsigned int numberOfTestCasesInSched() const
   { 
      return schedTestCases.size(); 
   }
 
   ValueType getTestCase(unsigned int index) const;

   void handleDoneTestCases
         ( const TestCase* testcase
         , bool hasSucceeded);

   
   std::string suitePath;
   std::list<ValueType> schedTestCases;
   
   TestCaseHierarchy* hierarchy; // Y
   const TestCaseFilter* nameFilter; // X
   TestFixtureResultCollector* collector; // X
   FixtureTagsFilter* tagsFilter; // X
   ComplexTestCaseFilter* complexFilter; // Y
};


///////////////////////////////////////////////////
TestHierarchyHandlerImpl::
TestHierarchyHandlerImpl
   ( const std::string& path
   , TestFixtureDesc* fixtureDesc 
   , const TestCaseFilter* filter
   , FixtureTagsFilter* fixtureTagsFilter
   , TestFixtureResultCollector* resultCollector)
   : suitePath(path)
   , nameFilter(filter)
   , collector(resultCollector)
   , tagsFilter(fixtureTagsFilter)
   , complexFilter(new ComplexTestCaseFilter(tagsFilter, filter))
{
   tagsFilter->startUp();
   
   hierarchy = new TestCaseHierarchy(fixtureDesc, complexFilter);
   hierarchy->getDirectSuccessors(0, this);
}

///////////////////////////////////////////////////
TestHierarchyHandlerImpl::
~TestHierarchyHandlerImpl()
{
   delete hierarchy;
   delete complexFilter;
}

///////////////////////////////////////////////////
bool
TestHierarchyHandlerImpl::
shouldReport(const TestCase* testcase) const
{
   return tagsFilter->shouldReport(testcase) &&
   nameFilter->isCaseMatch(testcase);
}

///////////////////////////////////////////////////
TestHierarchyHandler::ValueType
TestHierarchyHandlerImpl::
getTestCase(unsigned int index) const
{
   std::list<ValueType>::const_iterator iter = \
      schedTestCases.begin();

   for(unsigned int i=0; i < index; i++)
      iter++;

   bool userSpecified = shouldReport((*iter).first);
   return ValueType((*iter).first, userSpecified);
}

///////////////////////////////////////////////////
void
TestHierarchyHandlerImpl::
addTestCase
   ( const TestCase* testcase
   , bool userSpecified)
{
   if(tagsFilter->hasFailed(testcase))
   {
//      std::cout << "TESTCASE " << testcase->getName() << " FAILED" << std::endl;      
      handleDoneTestCases(testcase, false);
   }
   else if(tagsFilter->hasSucceeded(testcase))
   {
//      std::cout << "TESTCASE " << testcase->getName() << " SUCCEEDED" << std::endl;
      handleDoneTestCases(testcase, true);
   }
   else
   {
//      std::cout << "TESTCASE " << testcase->getName() << " IS SCHED" << std::endl;
     schedTestCases.push_back(ValueType(testcase, userSpecified));
   }
}

///////////////////////////////////////////////////
void
TestHierarchyHandlerImpl::
handleDoneTestCases
   ( const TestCase* testcase
   , bool hasSucceeded)
{
   tagsFilter->testDone(testcase, hasSucceeded);
   if(hasSucceeded)
   {
//      std::cout << "TESTCASE " << testcase->getName() << " has been run successfully" << std::endl;
      hierarchy->getDirectSuccessors(testcase, this);
   }
   else
   {
//      std::cout << "TESTCASE " << testcase->getName() << " failed to run " << std::endl;
      SkippedTestCases skippedTestCases(collector, tagsFilter);
      hierarchy->getSuccessors(testcase, &skippedTestCases);
   }

}

///////////////////////////////////////////////////
void
TestHierarchyHandlerImpl::
testDone
   ( const TestCase* testcase
   , bool hasSucceeded)
{
   std::list<ValueType>::iterator i = schedTestCases.begin();
   for(; i != schedTestCases.end(); i++)
   {
      if((*i).first == testcase)
      {
         handleDoneTestCases(testcase, hasSucceeded);
         return;
      }
   }
}

///////////////////////////////////////////////////
TestHierarchyHandler::
TestHierarchyHandler
   ( const std::string& suitePath
   , TestFixtureDesc* fixture
   , const TestCaseFilter* filter
   , FixtureTagsFilter* tagsFilter
   , TestFixtureResultCollector* collector)
   : This( new TestHierarchyHandlerImpl
         ( suitePath
		 , fixture
         , filter
         , tagsFilter
         , collector))
{
}

///////////////////////////////////////////////////
TestHierarchyHandler::
~TestHierarchyHandler()
{
   delete This;
}

///////////////////////////////////////////////////
const std::string& 
TestHierarchyHandler::
getSuitePath() const
{
	return This->suitePath;
}
///////////////////////////////////////////////////
void
TestHierarchyHandler::
testDone(const TestCase* testcase, bool hasSucceeded)
{
   return This->testDone(testcase, hasSucceeded);
}

///////////////////////////////////////////////////
unsigned int
TestHierarchyHandler::
numberOfTestCasesInSched() const
{
   return This->numberOfTestCasesInSched();
}

///////////////////////////////////////////////////
TestHierarchyHandler::ValueType
TestHierarchyHandler::
getTestCase(unsigned int index) const
{
   return This->getTestCase(index);
}

///////////////////////////////////////////////////

TESTNGPP_NS_END

