
#ifndef __TESTNGPP_TAGS_FILTERS_H
#define __TESTNGPP_TAGS_FILTERS_H

#include <testngpp/testngpp.h>

TESTNGPP_NS_START

struct Taggable;
struct TaggableObjFilter;
struct TagsFiltersImpl;

////////////////////////////////////////////////////////
struct TagsFilters
{
   TagsFilters();
   ~TagsFilters();

   void addNextFilter(const TaggableObjFilter*);

   const TaggableObjFilter* startOnNext();

   bool shouldBeFilteredThisTime(const Taggable* ) const;
   bool shouldBeFiltered(const Taggable* ) const;
   bool isPreFiltered(const Taggable* ) const;
   bool hasBeenFiltered(const Taggable* ) const;

   void dump() const;
private:
   TagsFiltersImpl * This;
};

////////////////////////////////////////////////////////

TESTNGPP_NS_END

#endif

