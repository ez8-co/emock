/***
    mockcpp is a generic C/C++ mock framework.
    Copyright (C) <2009>  <Darwin Yuan: darwin.yuan@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
***/

#include <iostream>
#include <testcpp/testcpp.hpp>

#include <mockcpp/mockcpp.hpp>
#include <mockcpp/StringConstraint.h>

#include <mockcpp/StringPredict.h>

USING_MOCKCPP_NS

class TestStringConstraint: public TESTCPP_NS::TestFixture
{
   struct StringPredictStub : public StringPredict
   {
     bool predict(const std::string& input, const std::string& target) const 
     {
        return input == target;
     }

     std::string toString(const std::string& target) const 
     {
         return std::string("<") + target + std::string(">");
     }
   };

private:

   TESTCPP_RCP checkpoint;
   StringConstraint* constraint;
   
public:
   void setUp()
   {
      checkpoint = TESTCPP_SET_RESOURCE_CHECK_POINT();

      constraint = new StringConstraint("abcd", new StringPredictStub());
   }

   void tearDown()
   {
      delete constraint;

      TESTCPP_VERIFY_RESOURCE_CHECK_POINT(checkpoint);
   }

   void testShouldBeAbleToEvalAStringWithSpecifiedPredict()
   {
      std::string input0("abcd");
      ASSERT_TRUE(constraint->eval(input0));

      std::string input1("aabcd");
      ASSERT_FALSE(constraint->eval(input1));
   }

   void testShouldBeAbleToEvalAPCharWithSpecifiedPredict()
   {
      char* input = (char*)"abcd";
      TS_ASSERT(constraint->eval(input));
   }

   void testShouldBeAbleToEvalAPConstCharWithSpecifiedPredict()
   {
      const char* input = "abcd";
      TS_ASSERT(constraint->eval(input));
   }

   void testShouldBeAbleToEvalAPUCharWithSpecifiedPredict()
   {
      unsigned char* input = (unsigned char*)"abcd";
      TS_ASSERT(constraint->eval(input));
   }

   void testShouldBeAbleToEvalAPConstUCharWithSpecifiedPredict()
   {
      const unsigned char* input = (const unsigned char*)"abcd";
      TS_ASSERT(constraint->eval(input));
   }

   void testShouldBeAbleToEvalANullPCharWithSpecifiedPredict()
   {
      char* input = 0;
      TS_ASSERT(!constraint->eval(input));
   }
};
