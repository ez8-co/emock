
#include <testngpp/runner/MatchAllTagsFilter.h>

TESTNGPP_NS_START

/////////////////////////////////////////////
bool
MatchAllTagsFilter::
matches(const Taggable* obj) const
{
   return true;
}

/////////////////////////////////////////////
std::string
MatchAllTagsFilter::
toString() const
{
   return "*";
}

TESTNGPP_NS_END


