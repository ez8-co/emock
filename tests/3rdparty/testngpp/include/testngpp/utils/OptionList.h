
#ifndef __TESTNGPP_OPTION_LIST_H
#define __TESTNGPP_OPTION_LIST_H

#include <list>
#include <string>

#include <testngpp/testngpp.h>
#include <testngpp/utils/StringList.h>

TESTNGPP_NS_START

struct OptionList
{
   typedef std::pair<std::string, std::string> Option;
   typedef std::list<Option> Options;
   typedef StringList Args;

   Options options;
   Args args;

   void parse(int argc, char** argv, const char* optstr);
   
   bool hasOption(const std::string& flag);

   std::string getSingleOption
         ( const std::string& option
         , const std::string& defaultValue);

   unsigned int
   getSingleUnsignedOption
         ( const std::string& option
         , const unsigned int defaultValue);
};

TESTNGPP_NS_END

#endif

