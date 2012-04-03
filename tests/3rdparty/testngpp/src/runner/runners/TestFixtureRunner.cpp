
#include <testngpp/comm/ExceptionKeywords.h>

#include <testngpp/utils/InternalError.h>

#include <testngpp/internal/Error.h>

#include <testngpp/internal/TestFixtureInfoReader.h>
#include <testngpp/internal/TestFixtureDesc.h>

#include <testngpp/listener/TestFixtureResultCollector.h>

#include <testngpp/runner/TestFixtureRunner.h>
#include <testngpp/runner/TestHierarchyRunner.h>
#include <testngpp/runner/TestHierarchyHandler.h>

#include <testngpp/runner/TestCaseFilter.h>
#include <testngpp/runner/FixtureTagsFilter.h>
#include <testngpp/runner/TestFixtureContext.h>


TESTNGPP_NS_START

/////////////////////////////////////////////////////////////////
struct TestFixtureRunnerImpl
{
   TestFixtureRunnerImpl(TestHierarchyRunner* runner);
   ~TestFixtureRunnerImpl();

   void run( TestFixtureContext* context
           , TestFixtureResultCollector* collector
           , const TestCaseFilter* filter
		   , const std::string& );

   TestHierarchyRunner* hierarchyRunner; // Y
};

/////////////////////////////////////////////////////////////////
TestFixtureRunnerImpl::
TestFixtureRunnerImpl(TestHierarchyRunner* runner)
	: hierarchyRunner(runner)
{
}

/////////////////////////////////////////////////////////////////
TestFixtureRunnerImpl::
~TestFixtureRunnerImpl()
{
   delete hierarchyRunner;
}

/////////////////////////////////////////////////////////////////
TestFixtureRunner::
TestFixtureRunner(TestHierarchyRunner* runner)
	: This(new TestFixtureRunnerImpl(runner))
{
}

/////////////////////////////////////////////////////////////////
TestFixtureRunner::~TestFixtureRunner()
{
   delete This;
}

/////////////////////////////////////////////////////////////////
void TestFixtureRunnerImpl::
run( TestFixtureContext* context
   , TestFixtureResultCollector* collector
   , const TestCaseFilter* filter
   , const std::string& suitePath)
{
   TestHierarchyHandler* handler = \
      new TestHierarchyHandler
	     ( suitePath
		 , context->getFixture()
		 , filter
		 , context->getTagsFilter()
		 , collector);

   collector->startTestFixture(context->getFixture());

   __TESTNGPP_TRY
   {
      hierarchyRunner->run(handler, collector);
   }
   __TESTNGPP_CATCH(Error& e)
   {
      collector->addFixtureError(context->getFixture(), e.what());
   }
   __TESTNGPP_CATCH(std::exception& e)
   {
       collector->addFixtureError(context->getFixture(), e.what());
   }   
   __TESTNGPP_CATCH_ALL
   {
      collector->addFixtureError(context->getFixture(), "Unknown Error");
   }
   __TESTNGPP_END_TRY

   collector->endTestFixture(context->getFixture());

   delete handler;
}


/////////////////////////////////////////////////////////////////
void TestFixtureRunner::
run( TestFixtureContext* context
   , TestFixtureResultCollector* collector
   , const TestCaseFilter* filter
   , const std::string& suitePath)
{
   return This->run(context, collector, filter, suitePath);
}

/////////////////////////////////////////////////////////////////

TESTNGPP_NS_END

