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
#include <mockcpp/Invocation.h>
#include <mockcpp/types/Any.h>
#include <mockcpp/types/AnyCast.h>

USING_MOCKCPP_NS

class TestInvocation: public TESTCPP_NS::TestFixture
{
public:

	/////////////////////////////////////////////////////////

	void testShouldBeAbleToPassAnyNumberOfParametersWithLimitOfConstructorParameterNumber()
	{
		Invocation inv(__FUNCTION__,1,2,3);

		TS_ASSERT(any_cast<int>(inv.getParameter(1)) == 1);
		TS_ASSERT(any_cast<int>(inv.getParameter(2)) == 2);
		TS_ASSERT(any_cast<int>(inv.getParameter(3)) == 3);

		TS_ASSERT(inv.getParameter(4).empty());
		TS_ASSERT(inv.getParameter(5).empty());
		TS_ASSERT(inv.getParameter(6).empty());
	}

	void testShouldBeAbleToGetAllInputParameters()
	{
		Invocation inv(__FUNCTION__, 1,2,3,4,5,6);

		TS_ASSERT(any_cast<int>(inv.getParameter(1)) == 1);
		TS_ASSERT(any_cast<int>(inv.getParameter(2)) == 2);
		TS_ASSERT(any_cast<int>(inv.getParameter(3)) == 3);
		TS_ASSERT(any_cast<int>(inv.getParameter(4)) == 4);
		TS_ASSERT(any_cast<int>(inv.getParameter(5)) == 5);
		TS_ASSERT(any_cast<int>(inv.getParameter(6)) == 6);
	}

	void testShouldEqualsDefaultAnyInstanceIfTryToGetThe0thParameter()
	{
		Invocation inv(__FUNCTION__, 1,2,3,4,5,6);
		TS_ASSERT(inv.getParameter(0).empty());
	}

	void testShouldEqualsDefaultAnyInstanceIfTryToGetTheNthParameterAndNIsGreaterThanNumberOfInputParameters()
	{
		Invocation inv(__FUNCTION__, 1,2,3,4,5,6);
		TS_ASSERT(inv.getParameter(7).empty());
	}

   void testShouldBeAbleToStringinizeCorrectly()
   {
      const std::string& ref = std::string("abcdef");
		Invocation inv(__FUNCTION__, ref);

      const std::string expected = "((std::string)\"" + ref  + "\")";
      TS_ASSERT_EQUALS(expected, inv.toString());
   }
};


