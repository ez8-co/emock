
#include <vector>

#include <testngpp/comm/ExceptionKeywords.h>

#include <testngpp/listener/TestResultCollector.h>

#include <testngpp/runner/TagsFilters.h>
#include <testngpp/runner/TestFilter.h>
#include <testngpp/runner/TestSuiteContext.h>
#include <testngpp/runner/TestRunnerContext.h>

#include <testngpp/runner/loaders/ModuleTestSuiteLoaderFactory.h>
#include <testngpp/runner/loaders/TestSuiteLoader.h>

TESTNGPP_NS_START

/////////////////////////////////////////////////////////////////
struct TestRunnerContextImpl
{
   TestRunnerContextImpl
      ( const StringList& nameOfSuites
      , TestResultCollector* collector
      , TagsFilters* tagsFilter
      , const TestFilter* filter);

   ~TestRunnerContextImpl();

private:

   void
   loadSuite
      ( const std::string& pathOfSuite
      , TestResultCollector* collector
      , TagsFilters* tagsFilter
      , const TestFilter* filter);

   void
   loadSuites
      ( const StringList& suites
      , TestResultCollector* collector
      , TagsFilters* tagsFilter
      , const TestFilter* filter);

   void
   unloadSuites();

public:

   std::vector<TestSuiteContext*> suites;
};

/////////////////////////////////////////////////////////////////
TestRunnerContextImpl::
TestRunnerContextImpl
      ( const StringList& suites
      , TestResultCollector* collector
      , TagsFilters* tagsFilter
      , const TestFilter* filter)
{

   loadSuites( suites
             , collector
             , tagsFilter
             , filter);
}

/////////////////////////////////////////////////////////////////
TestRunnerContextImpl::
~TestRunnerContextImpl()
{
   unloadSuites();
}

/////////////////////////////////////////////////////////////////
void
TestRunnerContextImpl::
loadSuite
      ( const std::string& pathOfSuite
      , TestResultCollector* collector
      , TagsFilters* tagsFilter
      , const TestFilter* filter)
{
   TestSuiteLoader* loader = ModuleTestSuiteLoaderFactory().create();

   __TESTNGPP_TRY
   {
      TestSuiteContext* suite = \
         new TestSuiteContext( loader
                             , pathOfSuite
                             , collector
                             , tagsFilter
                             , filter);

      suites.push_back(suite);
   }
   __TESTNGPP_CATCH_ALL
   {
      delete loader;
   }
   __TESTNGPP_END_TRY
}

/////////////////////////////////////////////////////////////////
void
TestRunnerContextImpl::
loadSuites( const StringList& suites
          , TestResultCollector* collector
          , TagsFilters* tagsFilter
          , const TestFilter* filter)
{
   StringList::Type::const_iterator i = suites.get().begin();
   for(; i != suites.get().end(); i++)
   {
      loadSuite(*i, collector, tagsFilter, filter);
   }
}

/////////////////////////////////////////////////////////////////
void
TestRunnerContextImpl::
unloadSuites()
{
   for(unsigned int i=0; i<suites.size(); i++)
   {
      delete suites[i];
   }

   suites.clear();
}

/////////////////////////////////////////////////////////////////
TestRunnerContext::
TestRunnerContext
      ( const StringList& suites
      , TestResultCollector* collector
      , TagsFilters* tagsFilter
      , const TestFilter* filter)
      : This( new TestRunnerContextImpl
               ( suites
               , collector
               , tagsFilter
               , filter))
{
}

/////////////////////////////////////////////////////////////////
TestRunnerContext::
~TestRunnerContext()
{
   delete This;
}

/////////////////////////////////////////////////////////////////
TestSuiteContext*
TestRunnerContext::
getSuite(unsigned int index) const
{
   if(index >= numberOfSuites())
   {
      return 0;
   }

   return This->suites[index];
}

/////////////////////////////////////////////////////////////////
unsigned int
TestRunnerContext::
numberOfSuites() const
{
   return This->suites.size();
}

/////////////////////////////////////////////////////////////////

TESTNGPP_NS_END

