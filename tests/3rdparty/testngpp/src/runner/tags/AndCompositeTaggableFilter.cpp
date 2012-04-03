
#include <list>
#include <algorithm>
#include <iostream>

#include <testngpp/utils/InternalError.h>

#include <testngpp/runner/AndCompositeTaggableFilter.h>
#include <testngpp/internal/Taggable.h>

TESTNGPP_NS_START

////////////////////////////////////////////////////////
struct AndCompositeTaggableFilterImpl
{
   typedef std::pair<const TaggableObjFilter*, bool> ValueType;
   typedef std::list<ValueType> Filters;

   Filters filters;

   ~AndCompositeTaggableFilterImpl();

   void addFilter(const TaggableObjFilter* filter, bool isComposite);
   bool matches(const Taggable* obj) const;
};

////////////////////////////////////////////////////////
AndCompositeTaggableFilterImpl::
~AndCompositeTaggableFilterImpl()
{
   Filters::iterator i = filters.begin();
   for(; i != filters.end(); i++)
   {
      if((*i).second)
         delete (*i).first;
   }
}

////////////////////////////////////////////////////////
AndCompositeTaggableFilter::
AndCompositeTaggableFilter()
   : This(new AndCompositeTaggableFilterImpl())
{
}

////////////////////////////////////////////////////////
AndCompositeTaggableFilter::
~AndCompositeTaggableFilter()
{
   delete This;
}

////////////////////////////////////////////////////
bool AndCompositeTaggableFilterImpl::
matches(const Taggable* obj) const
{
   Filters::const_iterator i = filters.begin();
   for(; i != filters.end(); i++)
   {
      if((*i).first == 0)
      {
         TESTNGPP_INTERNAL_ERROR(2015);
      }
      
      if(!(*i).first->matches(obj))
         return false;
   }

   return true;
}

////////////////////////////////////////////////////
void AndCompositeTaggableFilterImpl::
addFilter(const TaggableObjFilter* filter, bool isComposite) 
{
   filters.push_back(ValueType(filter, isComposite));
}

////////////////////////////////////////////////////
bool AndCompositeTaggableFilter::
matches(const Taggable* obj) const
{
   return This->matches(obj);
}

////////////////////////////////////////////////////////
void AndCompositeTaggableFilter::
addFilter(const TaggableObjFilter* filter, bool isComposite) 
{
   return This->addFilter(filter, isComposite);
}

////////////////////////////////////////////////////////
std::string 
AndCompositeTaggableFilter::
toString() const
{
   bool isFirst = true;
   std::string result("[");

   AndCompositeTaggableFilterImpl::Filters::const_iterator i = This->filters.begin();
   for(; i != This->filters.end(); i++)
   {
      if(isFirst)
      {
         isFirst = false;
      }
      else
      {
         result += " ";
      }

      result += (*i).first->toString();
   }
   
   result += "]";
   
   return result;
}

TESTNGPP_NS_END
