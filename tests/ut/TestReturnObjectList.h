/***
   emock is a cross-platform easy-to-use C++ Mock Framework based on mockcpp.
   Copyright [2017] [ez8.co] [orca <orca.zhang@yahoo.com>]

   This library is released under the Apache License, Version 2.0.
   Please see LICENSE file or visit https://github.com/ez8-co/emock for details.

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
#include <emock/emock.hpp>

USING_EMOCK_NS

int foo(int, int) {
	return 0;
}

class TestReturnObjectList : public TESTCPP_NS::TestFixture
{
public:

	void setUp() { }
	void tearDown() { }

	/////////////////////////////////////////////////////////
	void testShouldSupportReturnObjectList()
	{
		MOCKER(foo)
		   .expects(exactly(3))
		   .with(eq(1), eq(4))
		   .will(returnObjectList(3, 4, 5));

		int i = 1;

		TS_ASSERT_EQUALS(3, foo(i, 4));
		TS_ASSERT_EQUALS(4, foo(i, 4));
		TS_ASSERT_EQUALS(5, foo(i, 4));

		GlobalMockObject::verify();
	}

	void testShouldThrowExceptionIfTheTypeOfAReturnObjectMismatch()
	{
		MOCKER(foo)
		   .expects(exactly(3))
		   .with(eq(1), eq(4))
		   .will(returnObjectList(3, true, 5));

		int i = 1;

		TS_ASSERT_EQUALS(3, foo(i, 4));
		TS_ASSERT_THROWS(foo(i,4), Exception);
		//TS_ASSERT_EQUALS(4, foo.foo(i, 4));
		TS_ASSERT_EQUALS(5, foo(i, 4));

		GlobalMockObject::verify();
	}

	void testShouldThrowExceptionIfThereIsNoAvailableObjectsToReturn()
	{
		MOCKER(foo)
		   .stubs()
		   .with(eq(1), eq(4))
		   .will(returnObjectList(3, 4, 5));

		int i = 1;

		TS_ASSERT_EQUALS(3, foo(i, 4));
		TS_ASSERT_EQUALS(4, foo(i, 4));
		TS_ASSERT_EQUALS(5, foo(i, 4));

		TS_ASSERT_THROWS(foo(i,4), Exception);

		GlobalMockObject::verify();
	}

};

