
#include <iostream>

#include <testngpp/utils/InternalError.h>

#include <testngpp/runner/EmptyTagsFilter.h>
#include <testngpp/internal/Taggable.h>

TESTNGPP_NS_START

/////////////////////////////////////////////
bool
EmptyTagsFilter::
matches(const Taggable* obj) const
{
   if(obj == 0)
   {
      TESTNGPP_INTERNAL_ERROR(2016);
   }
      
   return obj->numberOfTags() == 0;
}

/////////////////////////////////////////////
std::string
EmptyTagsFilter::
toString() const
{
   return "$";
}

TESTNGPP_NS_END


