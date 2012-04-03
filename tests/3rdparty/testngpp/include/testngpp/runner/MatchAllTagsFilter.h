
#ifndef __TESTNGPP_MATCH_ALL_TAGS_FILTER_H
#define __TESTNGPP_MATCH_ALL_TAGS_FILTER_H

#include <testngpp/testngpp.h>
#include <testngpp/runner/TaggableObjFilter.h>

TESTNGPP_NS_START

////////////////////////////////////////////////////////
struct MatchAllTagsFilter
   : public TaggableObjFilter
{
   bool matches(const Taggable* ) const;

   std::string toString() const;
};

////////////////////////////////////////////////////////

TESTNGPP_NS_END

#endif

