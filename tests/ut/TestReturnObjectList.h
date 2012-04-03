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
#include <mockcpp/types/Any.h>
#include <mockcpp/ChainableMockObject.h>
#include <mockcpp/InvocationMockBuilder.h>
#include <mockcpp/ChainingMockHelper.h>

USING_MOCKCPP_NS

class Foo : public ChainableMockObject
{
public:
	Foo()
		: ChainableMockObject("Foo")
	{}

	int foo(int& i, unsigned long j)
	{
		return invoke<int>("foo")("foo",i, j);
	}
};

class TestReturnObjectList : public TESTCPP_NS::TestFixture
{
public:

	void setUp() { }
	void tearDown() { }

	/////////////////////////////////////////////////////////
	void testShouldSupportReturnObjectList()
	{
		Foo foo;

		foo.method("foo")
		   .expects(exactly(3))
		   .with(eq(1), eq((unsigned long)4))
		   .will(returnObjectList(3, 4, 5));

		int i = 1;

		TS_ASSERT_EQUALS(3, foo.foo(i, 4));
		TS_ASSERT_EQUALS(4, foo.foo(i, 4));
		TS_ASSERT_EQUALS(5, foo.foo(i, 4));

		foo.verify();
	}

	void testShouldThrowExceptionIfTheTypeOfAReturnObjectMismatch()
	{
		Foo foo;

		foo.method("foo")
		   .expects(exactly(3))
		   .with(eq(1), eq((unsigned long)4))
		   .will(returnObjectList(3, true, 5));

		int i = 1;

		TS_ASSERT_EQUALS(3, foo.foo(i, 4));
		TS_ASSERT_THROWS(foo.foo(i,4), Exception);
		//TS_ASSERT_EQUALS(4, foo.foo(i, 4));
		TS_ASSERT_EQUALS(5, foo.foo(i, 4));

		foo.verify();
	}

	void testShouldThrowExceptionIfThereIsNoAvailableObjectsToReturn()
	{
		Foo foo;

		foo.method("foo")
		   .stubs()
		   .with(eq(1), eq((unsigned long)4))
		   .will(returnObjectList(3, 4, 5));

		int i = 1;

		TS_ASSERT_EQUALS(3, foo.foo(i, 4));
		TS_ASSERT_EQUALS(4, foo.foo(i, 4));
		TS_ASSERT_EQUALS(5, foo.foo(i, 4));

		TS_ASSERT_THROWS(foo.foo(i,4), Exception);

		foo.verify();
	}

};

