
#include <list>
#include <algorithm>
#include <iostream>

#include <testngpp/runner/TagsFilters.h>
#include <testngpp/runner/FixtureTagsFilter.h>

#include <testngpp/internal/TestCase.h>


TESTNGPP_NS_START

////////////////////////////////////////////////////////
struct FixtureTagsFilterImpl
{
   FixtureTagsFilterImpl(TagsFilters* filter);
   ~FixtureTagsFilterImpl();

   void startUp();

   bool shouldRun(const TestCase* testcase) const;
   bool shouldReport(const TestCase* testcase) const;
   bool shouldStoreAsPreFiltered(const TestCase* testcase) const;
   
   void store(const TestCase* testcase, bool hasSucceeded);

   bool hasBeenRunAlready(const TestCase* testcase) const;
   bool hasFailedAlready(const TestCase* testcase) const;
   void cleanUpSucceededPreRunTestCases();   


   std::list<const TestCase*> preRunTestCases;
   std::list<const TestCase*> failedTestCases;
   TagsFilters* tagsFilters;
};

namespace
{
   struct CleanupRedundantPreRunTestCases
   {
      CleanupRedundantPreRunTestCases(TagsFilters* filters)
         : tagsFilters(filters)
      {}
      
      bool operator()(const TestCase* testcase)
      {
         return tagsFilters->hasBeenFiltered(testcase);
      }

      TagsFilters* tagsFilters;
   };
}

////////////////////////////////////////////////////////
FixtureTagsFilterImpl::
FixtureTagsFilterImpl(TagsFilters* filters)
   : tagsFilters(filters)
{
}

////////////////////////////////////////////////////////
FixtureTagsFilterImpl::
~FixtureTagsFilterImpl()
{
}

////////////////////////////////////////////////////////
bool
FixtureTagsFilterImpl::
hasBeenRunAlready(const TestCase* testcase) const
{
   std::list<const TestCase*>::const_iterator i = \
      preRunTestCases.begin();
   for(; i != preRunTestCases.end(); i++)
   {
      if((*i) == testcase)
         return true;
   }

   return false;
}

////////////////////////////////////////////////////////
bool
FixtureTagsFilterImpl::
hasFailedAlready(const TestCase* testcase) const
{
   std::list<const TestCase*>::const_iterator i = \
      failedTestCases.begin();
   for(; i != failedTestCases.end(); i++)
   {
      if((*i) == testcase)
         return true;
   }
   
   return false;
}

////////////////////////////////////////////////////////
bool
FixtureTagsFilterImpl::
shouldRun(const TestCase* testcase) const
{
   return tagsFilters->shouldBeFilteredThisTime(testcase);
}

////////////////////////////////////////////////////////
bool
FixtureTagsFilterImpl::
shouldReport(const TestCase* testcase) const
{
   return tagsFilters->shouldBeFiltered(testcase);
}

////////////////////////////////////////////////////////
bool
FixtureTagsFilterImpl::
shouldStoreAsPreFiltered(const TestCase* testcase) const
{
   return tagsFilters->isPreFiltered(testcase) &&
          !hasBeenRunAlready(testcase);
}

////////////////////////////////////////////////////////
void
FixtureTagsFilterImpl::
store(const TestCase* testcase, bool hasSucceeded)
{
   if(hasSucceeded && shouldStoreAsPreFiltered(testcase))
   {
      preRunTestCases.push_back(testcase);
   }
   
   if(!hasSucceeded && !hasFailedAlready(testcase))
   {
      failedTestCases.push_back(testcase);
   }
}

////////////////////////////////////////////////////////
void
FixtureTagsFilterImpl::
cleanUpSucceededPreRunTestCases()
{
   while(1)
   {
      std::list<const TestCase*>::iterator i = \
      std::find_if( preRunTestCases.begin()
                   , preRunTestCases.end()
                   , CleanupRedundantPreRunTestCases(tagsFilters)); 
      
      if(i == preRunTestCases.end())
      {
         break;
      }
      
      preRunTestCases.erase(i);
   }   
}

////////////////////////////////////////////////////////
void
FixtureTagsFilterImpl::
startUp()
{
   cleanUpSucceededPreRunTestCases(); 
}

////////////////////////////////////////////////////////
FixtureTagsFilter::
FixtureTagsFilter(TagsFilters* filters)
   : This(new FixtureTagsFilterImpl(filters))
{
}

////////////////////////////////////////////////////////
FixtureTagsFilter::
~FixtureTagsFilter()
{
   delete This;
}

////////////////////////////////////////////////////////
bool
FixtureTagsFilter::
shouldRun(const TestCase* testcase) const
{
   return This->shouldRun(testcase);
}

////////////////////////////////////////////////////////
bool
FixtureTagsFilter::
hasSucceeded(const TestCase* testcase) const
{
   return This->hasBeenRunAlready(testcase) ||
          This->tagsFilters->hasBeenFiltered(testcase);
}

////////////////////////////////////////////////////////
bool
FixtureTagsFilter::
hasFailed(const TestCase* testcase) const
{
   return This->hasFailedAlready(testcase);
}

////////////////////////////////////////////////////////
bool
FixtureTagsFilter::
shouldReport(const TestCase* testcase) const
{
   return This->shouldReport(testcase);
}

////////////////////////////////////////////////////////
void
FixtureTagsFilter::
startUp()
{
   return This->startUp();
}

////////////////////////////////////////////////////////
void
FixtureTagsFilter::
testDone(const TestCase* testcase, bool hasSucceeded) 
{
   This->store(testcase, hasSucceeded);
}

////////////////////////////////////////////////////////

TESTNGPP_NS_END
