#ifndef __TESTNGPP_TAGS_FILTER_RULE_H
#define __TESTNGPP_TAGS_FILTER_RULE_H

#include <string>

#include <testngpp/testngpp.h>

TESTNGPP_NS_START

////////////////////////////////////////////////////
struct TagsFilterRule
{
   virtual std::string toString() const = 0;

   virtual ~TagsFilterRule() {}
};

////////////////////////////////////////////////////

TESTNGPP_NS_END

#endif

