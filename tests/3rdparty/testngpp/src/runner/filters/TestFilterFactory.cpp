
#include <string>

#include <testngpp/runner/TestFilter.h>
#include <testngpp/runner/GeneralTestFilter.h>
#include <testngpp/runner/WildcardTestFilter.h>
#include <testngpp/runner/OrCompositeTestFilter.h>
#include <testngpp/runner/PosixFNMatcher.h>
#include <testngpp/runner/TestFilterFactory.h>

TESTNGPP_NS_START

namespace
{
   PosixFNMatcher* createMatcher(const std::string& pattern)
   {
      if(pattern == "")
      {
          return new PosixFNMatcher("*"); 
      }

      return new PosixFNMatcher(pattern);
   }
}
////////////////////////////////////////////////////////
const TestFilter*
TestFilterFactory::
getFilter(const StringList& filterOptions)
{
   if(filterOptions.get().size() == 0)
      return new WildcardTestFilter();

   OrCompositeTestFilter* orFilter = new OrCompositeTestFilter();

   StringList::Type::const_iterator i = filterOptions.get().begin();
   for(; i != filterOptions.get().end(); i++)
   {
      TestFilter* filter = 0;

      size_t pos = (*i).find_first_of(':');
      if(pos != std::string::npos)
      {
         filter = new GeneralTestFilter(
             createMatcher((*i).substr(0, pos)), \
             createMatcher((*i).substr(pos+1, (*i).size() - pos)));
      }
      else
      {
         filter = new GeneralTestFilter(
             createMatcher((*i).substr(0, pos)), 
             createMatcher("*"));
      }

      orFilter->addFilter(filter, true);
   }

   return orFilter;
}

////////////////////////////////////////////////////////
void 
TestFilterFactory::
returnFilter(const TestFilter* filter)
{
   if(filter != 0)
   {
      delete filter;
   }
}

////////////////////////////////////////////////////////

TESTNGPP_NS_END
