#ifndef __TESTNGPP_NAME_MATCHER_H
#define __TESTNGPP_NAME_MATCHER_H

#include <string>

#include <testngpp/testngpp.h>

TESTNGPP_NS_START

////////////////////////////////////////////////////
struct NameMatcher
{
   virtual bool matches(const std::string& name) const = 0;

   virtual std::string getPattern() const = 0;
   
   virtual ~NameMatcher() {}
};

////////////////////////////////////////////////////

TESTNGPP_NS_END

#endif

