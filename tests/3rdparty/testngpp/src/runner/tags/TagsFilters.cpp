
#include <vector>
#include <algorithm>

#include <iostream>

#include <testngpp/utils/InternalError.h>

#include <testngpp/internal/Error.h>
#include <testngpp/internal/Taggable.h>

#include <testngpp/runner/AndCompositeTaggableFilter.h>
#include <testngpp/runner/OrCompositeTaggableFilter.h>
#include <testngpp/runner/NotCompositeTaggableFilter.h>
#include <testngpp/runner/MatchAllTagsFilter.h>

#include <testngpp/runner/TaggableObjFilter.h>
#include <testngpp/runner/TagsFilters.h>


TESTNGPP_NS_START

////////////////////////////////////////////////////////
struct TagsFiltersImpl
{
   typedef std::pair<const TaggableObjFilter *, bool> ValueType;

   TagsFiltersImpl();
   ~TagsFiltersImpl();

   void addNextFilter(const TaggableObjFilter*);
   const TaggableObjFilter* startOnNext();

   bool shouldBeFilteredThisTime(const Taggable* obj) const;
   bool shouldBeFiltered(const Taggable* obj) const;
   bool isPreFiltered(const Taggable* obj) const;
   bool hasBeenFiltered(const Taggable* obj) const;
   
   void handleMatchAll();

   ValueType
   generateAllScopeFilter();

   void dump() const;
   
   std::vector<const TaggableObjFilter*> filters;
   OrCompositeTaggableFilter    allTagsFilter;
   OrCompositeTaggableFilter    doneTagsFilter; 
   NotCompositeTaggableFilter   notDoneFilter;
   int index;
};

////////////////////////////////////////////////////////
TagsFiltersImpl::
TagsFiltersImpl()
   : notDoneFilter(&doneTagsFilter, false)
   , index(-1)
{
}

////////////////////////////////////////////////////////
TagsFiltersImpl::
~TagsFiltersImpl()
{
   for(unsigned int i=0; i<filters.size(); i++)
   {
     delete filters[i];
   }

   filters.clear();
}

////////////////////////////////////////////////////////
void
TagsFiltersImpl::
addNextFilter(const TaggableObjFilter* filter)
{
   filters.push_back(filter);
   
   if(filter != 0)
   {
      allTagsFilter.addFilter(filter, false);
   }
}

TagsFiltersImpl::ValueType
TagsFiltersImpl::
generateAllScopeFilter()
{
   OrCompositeTaggableFilter* orFilter = new OrCompositeTaggableFilter();
   
   for(unsigned int i=0; i<filters.size(); i++)
   {
      if(filters[i] != 0)
      {
         orFilter->addFilter(filters[i], false);
      }
   }
   
   if(orFilter->isEmpty())
   {
      delete orFilter;
      return ValueType((const testngpp::TaggableObjFilter *)0, false);
   }
   else if(orFilter->isMalform())
   {
      ValueType result = orFilter->fetch();

      delete orFilter;

      return result;
   }

   return ValueType(orFilter, true);
}

namespace
{
   const TaggableObjFilter*
   generateMatchAllFilter(const TaggableObjFilter* filter, bool composite)
   {
      if(filter == 0)
         return new MatchAllTagsFilter();

      return new NotCompositeTaggableFilter(filter, composite);
   }
}
////////////////////////////////////////////////////////
void
TagsFiltersImpl::
handleMatchAll()
{
   ValueType filter = generateAllScopeFilter();

   bool hasMatchAll = false;
   for(unsigned int i=0; i<filters.size(); i++)
   {
      if(filters[i] == 0)
      {
         filters[i] = generateMatchAllFilter(filter.first, !hasMatchAll && filter.second);
         allTagsFilter.addFilter(filters[i], false);
         hasMatchAll = true;
      }
   }
   
   if(!hasMatchAll && filter.second)
   {
      delete filter.first;
   }
}

////////////////////////////////////////////////////////
void
TagsFiltersImpl::
dump() const
{
   std::cout << "Tags Spec : ";
   
   for(unsigned int i=0; i<filters.size(); i++)
   {
      if(i > 0) std::cout << " > " ;
      
      if(filters[i] != 0)
      {
         std::cout << filters[i]->toString();
      }
      else
      {
         std::cout << "*";
      }
   }
   
   std::cout << std::endl;
   
}
////////////////////////////////////////////////////////
const TaggableObjFilter*
TagsFiltersImpl::
startOnNext() 
{
   index++;

   if((unsigned int)index >= filters.size())
   {
      return 0;
   }

   if(index > 0)
   {
      doneTagsFilter.addFilter(filters[index-1], false);
   }
   else
   {
      handleMatchAll();
   }

   return filters[index];
}

////////////////////////////////////////////////////////
bool
TagsFiltersImpl::
shouldBeFilteredThisTime(const Taggable* obj) const
{
   if(index < 0 || (unsigned int)index >= filters.size())
   {
      TESTNGPP_INTERNAL_ERROR(2014);
   }
   
   return filters[index]->matches(obj) &&
          notDoneFilter.matches(obj);
}

////////////////////////////////////////////////////////
bool
TagsFiltersImpl::
shouldBeFiltered(const Taggable* obj) const
{
   return allTagsFilter.matches(obj);
}

////////////////////////////////////////////////////////
bool
TagsFiltersImpl::
isPreFiltered(const Taggable* obj) const
{
   return !filters[index]->matches(obj) &&
          !doneTagsFilter.matches(obj)  && 
           allTagsFilter.matches(obj);
}

////////////////////////////////////////////////////////
bool
TagsFiltersImpl::
hasBeenFiltered(const Taggable* obj) const
{
   return doneTagsFilter.matches(obj);
}

////////////////////////////////////////////////////////
TagsFilters::
TagsFilters()
   : This(new TagsFiltersImpl())
{
}

////////////////////////////////////////////////////////
TagsFilters::
~TagsFilters()
{
   delete This;
}

////////////////////////////////////////////////////////
void
TagsFilters::
addNextFilter(const TaggableObjFilter* filter)
{
   This->addNextFilter(filter);
}

////////////////////////////////////////////////////////
const TaggableObjFilter*
TagsFilters::
startOnNext() 
{
   return This->startOnNext();
}

////////////////////////////////////////////////////////
bool
TagsFilters::
shouldBeFilteredThisTime(const Taggable* obj) const
{
   return This->shouldBeFilteredThisTime(obj);
}

////////////////////////////////////////////////////////
bool
TagsFilters::
shouldBeFiltered(const Taggable* obj) const
{
   return This->shouldBeFiltered(obj);
}

////////////////////////////////////////////////////////
bool
TagsFilters::
isPreFiltered(const Taggable* obj) const
{
   return This->isPreFiltered(obj);
}

////////////////////////////////////////////////////////
bool
TagsFilters::
hasBeenFiltered(const Taggable* obj) const
{
   return This->hasBeenFiltered(obj);
}

////////////////////////////////////////////////////////
void
TagsFilters::
dump() const
{
   This->dump();
}


TESTNGPP_NS_END
