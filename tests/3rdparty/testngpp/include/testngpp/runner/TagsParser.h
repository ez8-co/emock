
#ifndef __TESTNGPP_TAGS_PARSER_H
#define __TESTNGPP_TAGS_PARSER_H

#include <testngpp/testngpp.h>

TESTNGPP_NS_START

struct TagsFilters;

struct TagsParser
{
    static TagsFilters* parse(const std::string& tagsSpec);
};

TESTNGPP_NS_END

#endif
