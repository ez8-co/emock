
#ifndef __TESTNGPP_AND_COMPOSITE_TESTCASE_FILTER_H
#define __TESTNGPP_AND_COMPOSITE_TESTCASE_FILTER_H

#include <testngpp/testngpp.h>
#include <testngpp/runner/TaggableObjFilter.h>

TESTNGPP_NS_START

struct Taggable;
struct TaggableObjFilter;
struct AndCompositeTaggableFilterImpl; 

////////////////////////////////////////////////////////
struct AndCompositeTaggableFilter 
   : public TaggableObjFilter
{
   AndCompositeTaggableFilter();
   ~AndCompositeTaggableFilter();

   void addFilter(const TaggableObjFilter* filter, bool isComposite=true);
   bool matches(const Taggable*) const;

   std::string toString() const;
   
private:
   AndCompositeTaggableFilterImpl * This;

};

////////////////////////////////////////////////////////

TESTNGPP_NS_END

#endif

