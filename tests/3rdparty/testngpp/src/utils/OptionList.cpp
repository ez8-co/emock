/**
    TestNG++ is a practical, easy-to-use C/C++ xUnit framework.
    Copyright (C) <2009>  <Arthur Yuan: arthur.ii.yuan@gmail.com>

    TestNG++ is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    TestNG++ is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with TestNG++.  If not, see <http://www.gnu.org/licenses/>.
**/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>

#ifdef _MSC_VER
#include <GetOpt.h>
#else
#include <unistd.h>
#endif

#include <testngpp/utils/OptionList.h>

TESTNGPP_NS_START

////////////////////////////////////////////////////
static void
parseOpt(OptionList* This, int argc, char** argv, const char* optstr)
{
   int c;
  	optind = 1;
   while ((c = ::getopt (argc, argv, optstr)) != -1)
   {
      char buf[2];
      sprintf(buf, "%c", c=='?'?optopt:c);

      This->options.push_back(
          OptionList::Option(buf, std::string(optarg==0?"":optarg)));
   }
}

////////////////////////////////////////////////////
void
OptionList::parse(int argc, char** argv, const char* optstr)
{
   opterr = 0;
   options.clear();
   args.clear();

   while(1)
   {
      optind = 1;

      parseOpt(this, argc, argv, optstr);

      argc -= optind;
      argv += optind;
      if(argc <= 0)
      {
        break;
      }

      args.add(argv[0]);
   }
}

////////////////////////////////////////////////////
bool 
OptionList::
hasOption(const std::string& flag)
{
   Options::const_iterator i = options.begin();
   for(; i != options.end(); i++)
   {
      if(i->first == flag)
         return true;
   }
   
   return false;
}

////////////////////////////////////////////////////
unsigned int
OptionList::
getSingleUnsignedOption
      ( const std::string& option
      , const unsigned int defaultValue)
{
    std::ostringstream oss;
    oss << defaultValue;

    std::string result = getSingleOption(option, oss.str());

    return atoi(result.c_str());
}

////////////////////////////////////////////////////
std::string
OptionList::
getSingleOption
      ( const std::string& option
      , const std::string& defaultValue)
{
   Options::const_iterator i = options.begin();
   for(; i != options.end(); i++)
   {
      if(i->first == option && i->second.size() > 0)
      {
         return i->second;
      }
   }

   return defaultValue;
}

TESTNGPP_NS_END

