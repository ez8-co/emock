
#ifndef __TESTNGPP_TAGS_FILTER_RESULT_COLLECTOR_H
#define __TESTNGPP_TAGS_FILTER_RESULT_COLLECTOR_H

#include <string>

#include <testngpp/testngpp.h>

#include <testngpp/listener/TestSuiteResultCollector.h>

TESTNGPP_NS_START

struct TagsFilterRule;

struct TagsFilterResultCollector
   : public TestSuiteResultCollector
{
	virtual void startTagsFiltering(const TagsFilterRule*) {}
	virtual void endTagsFiltering(const TagsFilterRule*) {}

   virtual ~TagsFilterResultCollector() {}
};

TESTNGPP_NS_END

#endif

