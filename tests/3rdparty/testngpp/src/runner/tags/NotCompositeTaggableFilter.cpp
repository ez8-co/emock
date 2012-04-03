
#include <iostream>

#include <testngpp/runner/NotCompositeTaggableFilter.h>
#include <testngpp/internal/Taggable.h>

TESTNGPP_NS_START

////////////////////////////////////////////////////////
struct NotCompositeTaggableFilterImpl
{
   const TaggableObjFilter* filter;
   bool isComposite;

   NotCompositeTaggableFilterImpl(const TaggableObjFilter*, bool);
   ~NotCompositeTaggableFilterImpl();

   bool matches(const Taggable* obj) const;
};

////////////////////////////////////////////////////////
NotCompositeTaggableFilterImpl::
NotCompositeTaggableFilterImpl(const TaggableObjFilter* tagsFilter, bool composite)
   : filter(tagsFilter)
   , isComposite(composite)
{
}

////////////////////////////////////////////////////////
NotCompositeTaggableFilterImpl::
~NotCompositeTaggableFilterImpl()
{
   if(isComposite && filter != 0)
      delete filter;
}

////////////////////////////////////////////////////////
NotCompositeTaggableFilter::
NotCompositeTaggableFilter(const TaggableObjFilter* filter, bool composite)
   : This(new NotCompositeTaggableFilterImpl(filter, composite))
{
}

////////////////////////////////////////////////////////
NotCompositeTaggableFilter::
~NotCompositeTaggableFilter()
{
   delete This;
}

////////////////////////////////////////////////////
bool NotCompositeTaggableFilterImpl::
matches(const Taggable* obj) const
{   
   if(filter == 0)
     return true;

   return !filter->matches(obj);
}

////////////////////////////////////////////////////
bool NotCompositeTaggableFilter::
matches(const Taggable* obj) const
{
   return This->matches(obj);
}

////////////////////////////////////////////////////////
std::string
NotCompositeTaggableFilter::
toString() const
{
   return "^" + This->filter->toString();
}

TESTNGPP_NS_END
