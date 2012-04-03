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

#include <cstring>
#include <ctype.h>
#include <iostream>
#include <cstring>

#include <testngpp/utils/StringToOptions.h>

TESTNGPP_NS_START

namespace
{
   struct ParseState
   {
      enum OptionFlag
      {
         NON,
         START,
         IN,
         END
      };

      int n;
      bool inDoubleQuote ;
      bool isLastCharABlank ;
      OptionFlag flag;

      ParseState()
         : n(0)
         , inDoubleQuote(false)
         , isLastCharABlank(true)
         , flag(NON)
      {}
   };

   #define PREDICT_CHECK(predict) do { \
      if(!(predict)) return false; \
   }while(0)

   ///////////////////////////////////////////////////
   bool scanInDoubleQuote(ParseState& state, char c)
   {
      PREDICT_CHECK(state.inDoubleQuote);

      if(c == '\"')
      {
         state.inDoubleQuote = false;
      }

      state.flag = ParseState::IN;

      return true;
   }

   ///////////////////////////////////////////////////
   bool scanInBlank(ParseState& state, char c)
   {
      PREDICT_CHECK(::isspace(c));

      if(!state.isLastCharABlank)
      {
         ++state.n;
      }

      state.flag = state.isLastCharABlank ? \
         ParseState::NON: ParseState::END;

      return true;
   }

   ///////////////////////////////////////////////////
   bool scanInNonBlank(ParseState& state, char c)
   {
      PREDICT_CHECK(!::isspace(c));

      if(c == '\"')
      {
         state.inDoubleQuote = true;
      }

      state.flag = state.isLastCharABlank ? \
         ParseState::START : ParseState::IN;

      return true;
   }

   ///////////////////////////////////////////////////
   void scan(ParseState& state, char c)
   {
      scanInDoubleQuote(state, c) || scanInBlank(state, c) || scanInNonBlank(state, c);
	  state.isLastCharABlank = ::isspace(c)?true:false;
   }

   char* createArg(char* s, char* e)
   {
      size_t len = e-s;
      char* p = new char[len + 1];
      ::strncpy(p, s, len);
      p[len] = 0;
      return p;
   }

   ///////////////////////////////////////////////////
   char** parseToCArgs(const std::string& s, int argc)
   {
      char** argv = new char*[argc];
      char* p = const_cast<char*>(s.c_str());
      ParseState state;
      char* pArg = 0;

      for(; (*p) != 0; p++)
      {
         scan(state, *p);

         switch(state.flag)
         {
         case ParseState::START:
            pArg = p; break;
         case ParseState::END:
            argv[state.n - 1] = createArg(pArg, p);
            break;
         case ParseState::NON:
         case ParseState::IN:
         default:
               break;
         }
      }

      return argv;
   }
}

int StringToOptions::
getNumberOfArgsInString(const std::string& s)
{
   std::string str = s + " ";
   char* p = const_cast<char*>(str.c_str());
   ParseState state;

   for(; (*p) != 0; p++)
   {
      scan(state, *p);
   }

   return state.n;
}

StringToOptions::CArgs
StringToOptions::parse(const std::string& s)
{
   int argc = getNumberOfArgsInString(s);
   if(argc == 0)
     return CArgs(argc, (char **)0);

   return CArgs(argc, parseToCArgs(s + " ", argc));
}


TESTNGPP_NS_END
