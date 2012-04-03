
#include <testngpp/runner/TestFilter.h>
#include <testngpp/runner/GeneralTestFilter.h>
#include <testngpp/runner/NameMatcher.h>

#include <testngpp/internal/TestFixtureInfoReader.h>
#include <testngpp/internal/TestCase.h>

TESTNGPP_NS_START

struct GeneralTestFilterImpl
{
   GeneralTestFilterImpl(NameMatcher* fMatcher, NameMatcher* cMatcher);

   ~GeneralTestFilterImpl();
   NameMatcher* fixtureMatcher;
   NameMatcher* caseMatcher;
};

////////////////////////////////////////////////////////
GeneralTestFilterImpl::
GeneralTestFilterImpl(NameMatcher* fMatcher, NameMatcher* cMatcher)
   : fixtureMatcher(fMatcher) , caseMatcher(cMatcher)
{
}
////////////////////////////////////////////////////////
GeneralTestFilterImpl::~GeneralTestFilterImpl()
{
   delete fixtureMatcher;
   delete caseMatcher;
}
////////////////////////////////////////////////////////
GeneralTestFilter::
GeneralTestFilter(NameMatcher* fixtureMatcher, NameMatcher* caseMatcher)
   : This(new GeneralTestFilterImpl(fixtureMatcher, caseMatcher))
{
}

////////////////////////////////////////////////////////
GeneralTestFilter::~GeneralTestFilter()
{
   delete This;
}

bool GeneralTestFilter::
isFixtureMatch(const TestFixtureInfoReader* fixture) const
{
   return This->fixtureMatcher->matches(fixture->getName());
}

////////////////////////////////////////////////////
bool GeneralTestFilter::
isCaseMatch(const TestCase* testcase) const
{
   return This->fixtureMatcher->matches(testcase->getNameOfFixture())
      &&  This->caseMatcher->matches(testcase->getName());
}

////////////////////////////////////////////////////////

TESTNGPP_NS_END
