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

#include <testcpp/testcpp.hpp>



#include <mockcpp/IsStringStartWith.h>

USING_MOCKCPP_NS

class TestIsStringStartWith: public TESTCPP_NS::TestFixture
{
private:

   TESTCPP_RCP checkpoint;

public:

   void setUp()
   {
      checkpoint = TESTCPP_SET_RESOURCE_CHECK_POINT();

   }
   void tearDown()
   {
      TESTCPP_VERIFY_RESOURCE_CHECK_POINT(checkpoint);
   }

	/////////////////////////////////////////////////////////

	void testShouldReturnTrueIfTheParameterDoesStartWithSpecifiedString()
	{
       IsStringStartWith constraint;

       std::string input("abcdefg");
       std::string target("abcd");

       TS_ASSERT(constraint.predict(input, target));
	}

	void testShouldReturnFalseIfTheParameterDoesNotStartWithSpecifiedString()
	{
       IsStringStartWith constraint;

       std::string input("abcfefg");
       std::string target("abcd");

       TS_ASSERT(!constraint.predict(input, target));
	}

	void testShouldBeAbleConvertToRequiredFormattedString()
	{
       IsStringStartWith constraint;

       TS_ASSERT_EQUALS(std::string("startWith(\"abcd\")"), constraint.toString("abcd"));
	}
};

