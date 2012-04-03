
#include <testngpp/runner/TestFilter.h>
#include <testngpp/runner/WildcardTestFilter.h>

TESTNGPP_NS_START

////////////////////////////////////////////////////////
bool WildcardTestFilter::
isFixtureMatch(const TestFixtureInfoReader* fixture) const
{
   return true;
}

////////////////////////////////////////////////////
bool WildcardTestFilter::
isCaseMatch(const TestCase* testcase) const
{
   return true;
}

////////////////////////////////////////////////////////

TESTNGPP_NS_END
