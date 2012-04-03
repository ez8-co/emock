
#include <vector>

#include <testngpp/comm/ExceptionKeywords.h>

#include <testngpp/utils/InternalError.h>

#include <testngpp/internal/Error.h>
#include <testngpp/internal/TestSuiteDesc.h>

#include <testngpp/listener/TestResultCollector.h>

#include <testngpp/runner/loaders/TestSuiteLoader.h>

#include <testngpp/runner/TagsFilters.h>
#include <testngpp/runner/TestFilter.h>
#include <testngpp/runner/TestFixtureContext.h>
#include <testngpp/runner/TestSuiteDescEntryNameGetter.h>

#include <testngpp/runner/TestSuiteContext.h>
 
TESTNGPP_NS_START
 
/////////////////////////////////////////////////////////////////
namespace
{
   const std::string testngppTestSuiteDescGetter("___testngpp_test_suite_desc_getter");
}

/////////////////////////////////////////////////////////////////

struct TestSuiteContextImpl
   : public TestSuiteDescEntryNameGetter
{
   TestSuiteContextImpl
      ( TestSuiteLoader* loader
      , const std::string& path
      , TestResultCollector* collector
      , TagsFilters* tagsFilter
      , const TestFilter* filter);

   ~TestSuiteContextImpl();

   std::string getDescEntryName() const
   { return testngppTestSuiteDescGetter; }

private:

   void load( const std::string& path );
   void loadFixtures( TagsFilters* tagsFilter 
                    , const TestFilter* filter);

   void unloadFixtures();

   void clear();

private:

   TestSuiteLoader* suiteLoader; // Y
   TestResultCollector* resultCollector; //X
public:

   std::vector<TestFixtureContext*> fixtures;
   TestSuiteDesc* suite; //X
   std::string suitePath;

};

/////////////////////////////////////////////////////////////////
TestSuiteContextImpl::
TestSuiteContextImpl
      ( TestSuiteLoader* loader
      , const std::string& path
      , TestResultCollector* collector
      , TagsFilters* tagsFilter
      , const TestFilter* filter)
      : suiteLoader(loader)
      , resultCollector(collector)
	  , suite(0)
	  , suitePath(path)
{
   __TESTNGPP_TRY
   {
      load(path);
      loadFixtures(tagsFilter, filter);
   }
   __TESTNGPP_CATCH_ALL
   {
      clear();
      throw;
   }
   __TESTNGPP_END_TRY
}

/////////////////////////////////////////////////////////////////
TestSuiteContextImpl::
~TestSuiteContextImpl()
{
   clear();

   delete suiteLoader;
}

/////////////////////////////////////////////////////////////////
void
TestSuiteContextImpl::
clear()
{
   unloadFixtures();
   suiteLoader->unload();
}

/////////////////////////////////////////////////////////////////
void
TestSuiteContextImpl::
loadFixtures
   ( TagsFilters* tagsFilter 
   , const TestFilter* filter)
{
   for(unsigned int i=0; i<suite->getNumberOfTestFixtures(); i++)
   {
      TestFixtureDesc* fixture = suite->getTestFixture(i);
      if(filter->isFixtureMatch((const TestFixtureInfoReader*)fixture))
      {
         fixtures.push_back(new TestFixtureContext(fixture, tagsFilter));
      }
   }
}

/////////////////////////////////////////////////////////////////
void
TestSuiteContextImpl::
unloadFixtures()
{
   for(unsigned int i=0; i < fixtures.size(); i++)
   {
      delete fixtures[i];
   }

   fixtures.clear();
}

/////////////////////////////////////////////////////////////////
void
TestSuiteContextImpl::
load( const std::string& path )
{
   const StringList searchingPaths;

   __TESTNGPP_TRY
   {
      suite = suiteLoader->load(searchingPaths, path, this);
   }
   __TESTNGPP_CATCH(std::exception& e)
   {
      resultCollector->addError
         ( "test suite \"" + path + "\" can't be loaded : " + e.what() );
      throw;
   }
   __TESTNGPP_END_TRY
}

/////////////////////////////////////////////////////////////////
TestSuiteDesc* 
TestSuiteContext::
getSuite() const
{
   return This->suite;
}

/////////////////////////////////////////////////////////////////
unsigned int 
TestSuiteContext::
numberOfFixtures() const
{
   return This->fixtures.size();
}

/////////////////////////////////////////////////////////////////
TestFixtureContext* 
TestSuiteContext::
getFixture(unsigned int index) const
{
   if(index >= This->fixtures.size())
   {
      TESTNGPP_INTERNAL_ERROR(2017);
   }

   return This->fixtures[index];
}

const std::string&
TestSuiteContext::
getSuitePath() const
{
	return This->suitePath;
}
/////////////////////////////////////////////////////////////////
TestSuiteContext::
TestSuiteContext
      ( TestSuiteLoader* loader
      , const std::string& path
      , TestResultCollector* collector
      , TagsFilters* tagsFilter
      , const TestFilter* filter
      )
      : This( new TestSuiteContextImpl
               ( loader
               , path
               , collector
               , tagsFilter
               , filter)
      )
{
}
            
/////////////////////////////////////////////////////////////////
TestSuiteContext::
~TestSuiteContext()
{
   delete This;
}

/////////////////////////////////////////////////////////////////
TESTNGPP_NS_END

