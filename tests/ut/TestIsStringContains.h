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

#include <mockcpp/IsStringContains.h>

USING_MOCKCPP_NS

class TestIsStringContains: public TESTCPP_NS::TestFixture
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

	void testShouldReturnTrueIfTheInputDoesContainsSpecifiedString()
	{
       IsStringContains predict;

       std::string input("efgabcd12");
       std::string target("abcd");

       TS_ASSERT(predict.predict(input, target));
	}

	void testShouldReturnTrueIfTheInputStartWithSpecifiedString()
	{
       IsStringContains predict;

       std::string input("gabcd12");
       std::string target("abcd");

       TS_ASSERT(predict.predict(input, target));
	}

	void testShouldReturnTrueIfTheInputEndWithSpecifiedString()
	{
       IsStringContains predict;

       std::string input("g12abcd");
       std::string target("abcd");

       TS_ASSERT(predict.predict(input, target));
	}

	void testShouldReturnTrueIfTheInputEqualsSpecifiedString()
	{
       IsStringContains predict;

       std::string input("abcd");
       std::string target("abcd");

       TS_ASSERT(predict.predict(input, target));
	}

	void testShouldReturnFalseIfTheInputDoesNotContainsSpecifiedString()
	{
       IsStringContains predict;

       std::string input("efgafbcd12");
       std::string target("abcd");

       TS_ASSERT(!predict.predict(input, target));
	}

	void testShouldBeAbleConvertToRequiredFormattedString()
	{
       IsStringContains predict;

       TS_ASSERT_EQUALS(std::string("contains(\"abcd\")"), predict.toString("abcd"));
	}
};

