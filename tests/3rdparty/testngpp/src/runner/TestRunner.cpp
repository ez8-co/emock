
#include <iostream>

#include <testngpp/comm/ExceptionKeywords.h>

#include <testngpp/internal/Error.h>
#include <testngpp/utils/InternalError.h>
#include <testngpp/utils/StupidTimer.h>

#include <testngpp/listener/TestResultCollector.h>

#include <testngpp/runner/loaders/ModuleTestListenerLoaderFactory.h>
#include <testngpp/runner/loaders/ModuleTestSuiteLoaderFactory.h>

#include <testngpp/runner/TestSuiteRunner.h>
#include <testngpp/runner/TestFixtureRunnerFactory.h>

#include <testngpp/runner/TestFilter.h>
#include <testngpp/runner/TestFilterFactory.h>
#include <testngpp/runner/SimpleTestResultManager.h>
#include <testngpp/runner/TestResultManager.h>
#include <testngpp/runner/TagsFilters.h>
#include <testngpp/runner/TaggableObjFilter.h>
#include <testngpp/runner/TagsParser.h>
#include <testngpp/runner/TestRunnerContext.h>

#include <testngpp/runner/TestRunner.h>

TESTNGPP_NS_START

struct TestRunnerImpl
{

   TestFixtureRunner * fixtureRunner;
   TestSuiteRunner * suiteRunner;

   TestResultManager *resultManager;

   bool hasFailures;

   TestRunnerImpl();
   ~TestRunnerImpl();
   
   void createSuiteRunner
      ( bool useSandbox
      , unsigned int maxConcurrent);

   void runTestSuite
      (TestSuiteContext* suite, const TestFilter* filter);

   void runAllTests
      ( const StringList& suites
      , TagsFilters* tagsFilters
      , const TestFilter* filter);

   void loadListeners
      ( const StringList& searchingPaths
      , const StringList& listeners);

   void runAllSuites
      ( TestRunnerContext* context, const TestFilter* filter);

   TestRunnerContext* 
   loadSuites
      ( const StringList& suites
      , TagsFilters* tagsFilters
      , const TestFilter* filter);

   void runTests
      ( const StringList& suites
      , TagsFilters* tagsFilters
      , const TestFilter* filter);
};

///////////////////////////////////////////////////////
TestRunnerImpl::TestRunnerImpl()
   : fixtureRunner(0)
   , suiteRunner(0)
   , hasFailures(false)
{
   resultManager = \
      new SimpleTestResultManager(
         new ModuleTestListenerLoaderFactory());
}

///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
TestRunnerImpl::
~TestRunnerImpl()
{
   if(suiteRunner != 0)
   {
      delete suiteRunner;
   }

   if(fixtureRunner != 0)
   {
      TestFixtureRunnerFactory::
           destroyInstance(fixtureRunner);
   }

   if(resultManager != 0)
   {
      delete resultManager;
   }
}

///////////////////////////////////////////////////////
void
TestRunnerImpl::
loadListeners
   ( const StringList& searchingPaths
   , const StringList& listeners)
{
   resultManager->load(searchingPaths, listeners);
}

///////////////////////////////////////////////////////
TestRunnerContext*
TestRunnerImpl::
loadSuites
   ( const StringList& suites
   , TagsFilters* tagsFilters
   , const TestFilter* filter)
{
   return new TestRunnerContext
            ( suites
            , resultManager->getResultCollector()
            , tagsFilters
            , filter);
}

///////////////////////////////////////////////////////
void
TestRunnerImpl::
createSuiteRunner(bool useSandbox, unsigned int maxConcurrent)
{
   fixtureRunner = TestFixtureRunnerFactory::createInstance(useSandbox, maxConcurrent);
   suiteRunner = new TestSuiteRunner(fixtureRunner, resultManager->getResultCollector());
}

///////////////////////////////////////////////////////
void TestRunnerImpl::
runTestSuite
      (TestSuiteContext* suite, const TestFilter* filter)
{
   __TESTNGPP_TRY
   {
     suiteRunner->run(suite, filter);
   }
   __TESTNGPP_CATCH(Error& e)
   {
      std::cerr << e.what() << std::endl;
      hasFailures = true;
   }
   __TESTNGPP_CATCH_ALL
   {
      std::cerr << TESTNGPP_INTERNAL_ERROR(5001) << std::endl;
      hasFailures = true;
   }
   __TESTNGPP_END_TRY
}


void
TestRunnerImpl::
runAllSuites
      ( TestRunnerContext* context, const TestFilter* filter)
{
   for(unsigned int i=0; i<context->numberOfSuites(); i++)
   {
      runTestSuite(context->getSuite(i), filter);
   }
}
///////////////////////////////////////////////////////
void
TestRunnerImpl::
runAllTests
      ( const StringList& suites
      , TagsFilters* tagsFilters
      , const TestFilter* filter)
{
   TestResultCollector* collector = \
      resultManager->getResultCollector();

   TestRunnerContext* context = \
      loadSuites(suites, tagsFilters, filter);

   while(1)
   {
      const TaggableObjFilter* taggableFilter = \
         tagsFilters->startOnNext();
      if(taggableFilter == 0)
      {
         break;
      }

      collector->startTagsFiltering(taggableFilter);
      runAllSuites(context, filter);
      collector->endTagsFiltering(taggableFilter);
   }

   delete context;
}

///////////////////////////////////////////////////////
void
TestRunnerImpl::
runTests
      ( const StringList& suites
      , TagsFilters* tagsFilters
      , const TestFilter* filter)
{
   resultManager->startTest();

   StupidTimer timer;
   timer.start();

   runAllTests(suites, tagsFilters, filter);

   timeval tv = timer.stop();
   resultManager->endTest(tv.tv_sec, tv.tv_usec);

   if(resultManager->hasFailure())
   {
      hasFailures = true;
   }
}

///////////////////////////////////////////////////////
TestRunner::TestRunner()
   : This(new TestRunnerImpl())
{
}

///////////////////////////////////////////////////////
TestRunner::~TestRunner()
{
   delete This;
}

///////////////////////////////////////////////////////
int
TestRunner::runTests( bool useSandbox
                    , unsigned int maxConcurrent
                    , const StringList& suitePaths
                    , const StringList& listenerNames
                    , const StringList& searchingPaths
                    , const StringList& fixtures
                    , const std::string& tagsFilterOption)
{
   This->createSuiteRunner(useSandbox, maxConcurrent);
   This->loadListeners(searchingPaths, listenerNames);

   const TestFilter* filter = TestFilterFactory::getFilter(fixtures);

   __TESTNGPP_TRY
   {
      TagsFilters* tagsFilter = TagsParser::parse(tagsFilterOption);
      This->runTests(suitePaths, tagsFilter, filter);
      delete tagsFilter;
   }
   __TESTNGPP_CATCH(Error& e)
   {
      std::cerr << e.what() << std::endl;
      This->hasFailures = true;
   }
   __TESTNGPP_CATCH_ALL
   {
      This->hasFailures = true;
   }
   __TESTNGPP_END_TRY
   
   TestFilterFactory::returnFilter(filter);

   return This->hasFailures ? -1 : 0;
}

///////////////////////////////////////////////////////

TESTNGPP_NS_END

