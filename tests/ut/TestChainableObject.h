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

class TestChainableObject : public TESTCPP_NS::TestFixture
{
	class Foo : public ChainableMockObject
	{
	public:
		Foo()
			: ChainableMockObject("Foo")
		{}

		int foo(int& i, unsigned long j)
		{
			return invoke<int>("foo")("foo", i, j);
		}
	};

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
	void testShouldSupportOrderingExpectationByAfter()
	{
		Foo foo ;

		foo.method("foo")
		   .expects(once())
		   .with(eq(1), eq((unsigned long)2))
		   .will(returnValue(10))
		   .id("1");

		foo.method("foo")
		   .expects(once())
		   .with(eq(2), eq((unsigned long)2))
		   .after("1")
		   .will(returnValue(12));

		int i = 2, j = 1;

		TS_ASSERT_EQUALS(10, foo.foo(j, 2));
		TS_ASSERT_EQUALS(12, foo.foo(i, 2));

		foo.verify();
	}

	void testShouldSupportOrderingExpectationByBefore()
	{
		Foo foo;

		foo.method("foo")
		   .expects(once())
		   .before("1")
		   .with(eq(2), eq((unsigned long)2))
		   .will(returnValue(10));

		foo.method("foo")
		   .expects(once())
		   .with(eq(1), eq((unsigned long)2))
		   .will(returnValue(10))
		   .id("1");

		int i = 2, j = 1;

		TS_ASSERT_EQUALS(10, foo.foo(i, 2));
		TS_ASSERT_EQUALS(10, foo.foo(j, 2));

		foo.verify();
	}

	void testShouldFailIfInvocationOutOfOrder()
	{
		Foo foo;

		foo.method("foo")
		   .expects(once())
		   .with(eq(1), eq((unsigned long)2))
		   .will(returnValue(10))
		   .id("1");

		foo.method("foo")
		   .expects(once())
		   .before("1")
		   .with(eq(2), eq((unsigned long)2))
		   .will(returnValue(10));

		int i = 2, j = 1;

		TS_ASSERT_EQUALS(10, foo.foo(j, 2));

		TS_ASSERT_THROWS(foo.foo(i,2), Exception);

		foo.verify();
	}

	void testShouldFailIfInvocationOutOfOrder2()
	{
		Foo foo;

		foo.method("foo")
	   	   .expects(once())
	   	   .with(eq(1), eq((unsigned long)2))
		   .will(returnValue(10))
            .id("1");

		foo.method("foo")
		   .expects(once())
		   .with(eq(2), eq((unsigned long)2))
		   .after("1")
		   .will(returnValue(10));

		int i = 2, j = 1;

		TS_ASSERT_THROWS(foo.foo(i, 2), Exception);
		TS_ASSERT_EQUALS(10, foo.foo(j, 2));

		foo.verify();
	}

	void testShouldFailIfReturnedTypeDoesNotMatchRequiredType2()
	{
		Foo foo;

		foo.method("foo")
		   .defaults()
	  	   .will(returnValue(true));

		int i = 2;

		TS_ASSERT_THROWS(foo.foo(i, 2), Exception);

		foo.verify();
	}

	void testShouldFailIfReturnedTypeDoesNotMatchRequiredType()
	{
		Foo foo;

		foo.method("foo")
		   .expects(once())
		   .with(eq(1), eq((unsigned long)2))
		   .will(returnValue(false));

		int i = 1;

		TS_ASSERT_THROWS(foo.foo(i,2), Exception);

		foo.verify();
	}

	void testShouldFailIfInvokedTimesIsMoreThanExpectedTimes()
	{
		Foo foo;

		foo.method("foo")
		   .expects(never())
		   .with(eq(2), eq((unsigned long)2))
		   .will(returnValue(10));

		int i = 2;

		TS_ASSERT_THROWS(foo.foo(i,2), Exception);

		foo.verify();
	}
};

