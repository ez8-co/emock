
#ifndef __TESTNGPP_NOT_COMPOSITE_TAGGABLE_H
#define __TESTNGPP_NOT_COMPOSITE_TAGGABLE_H

#include <testngpp/testngpp.h>
#include <testngpp/runner/TaggableObjFilter.h>

TESTNGPP_NS_START

struct NotCompositeTaggableFilterImpl;

////////////////////////////////////////////////////////
struct NotCompositeTaggableFilter
   : public TaggableObjFilter
{
   NotCompositeTaggableFilter(const TaggableObjFilter*, bool composite=true);
   ~NotCompositeTaggableFilter();

   bool matches(const Taggable*) const;

   std::string toString() const;
   
private:
   NotCompositeTaggableFilterImpl * This;

};

////////////////////////////////////////////////////////

TESTNGPP_NS_END

#endif

