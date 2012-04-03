
#ifndef __TESTNGPP_STRING_TO_OPTIONS_H
#define __TESTNGPP_STRING_TO_OPTIONS_H

#include <list>
#include <string>

#include <testngpp/testngpp.h>

TESTNGPP_NS_START

struct StringToOptions
{
   typedef std::pair<int, char**> CArgs;

   static int getNumberOfArgsInString(const std::string& s);
   static CArgs parse(const std::string& s);
};

TESTNGPP_NS_END

#endif

