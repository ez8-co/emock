
#ifndef __TESTNGPP_GENERAL_TAGS_FILTER_H
#define __TESTNGPP_GENERAL_TAGS_FILTER_H

#include <testngpp/testngpp.h>
#include <testngpp/runner/TaggableObjFilter.h>

TESTNGPP_NS_START

struct NameMatcher;

struct GeneralTagsFilterImpl;

////////////////////////////////////////////////////////
struct GeneralTagsFilter
   : public TaggableObjFilter
{
   GeneralTagsFilter(NameMatcher*);
   ~GeneralTagsFilter();

   bool matches(const Taggable* ) const;

   std::string toString() const;

private:
   GeneralTagsFilterImpl * This;

};

////////////////////////////////////////////////////////

TESTNGPP_NS_END

#endif

