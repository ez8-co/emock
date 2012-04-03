
#ifndef __TESTNGPP_OR_COMPOSITE_TAGGABLE_FILTER_H
#define __TESTNGPP_OR_COMPOSITE_TAGGABLE_FILTER_H

#include <algorithm>

#include <testngpp/testngpp.h>
#include <testngpp/runner/TaggableObjFilter.h>

TESTNGPP_NS_START

struct Taggable;
struct OrCompositeTaggableFilterImpl;

////////////////////////////////////////////////////////
struct OrCompositeTaggableFilter
   : public TaggableObjFilter
{
   OrCompositeTaggableFilter();
   ~OrCompositeTaggableFilter();

   void addFilter(const TaggableObjFilter* filter, bool isComposite=true);

   bool isMalform() const;
   bool isEmpty() const;
   
   std::pair<const TaggableObjFilter*, bool> fetch();

   bool matches(const Taggable* ) const;

   std::string toString() const;
   
private:
   OrCompositeTaggableFilterImpl * This;

};

////////////////////////////////////////////////////////

TESTNGPP_NS_END

#endif

