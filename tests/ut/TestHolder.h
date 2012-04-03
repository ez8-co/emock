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
#include <mockcpp/types/ValueHolder.h>
#include <mockcpp/types/RefHolder.h>

USING_MOCKCPP_NS

struct A
{
	A(int v) : val(v) {}

	bool operator==(const A& rhs) const
   {
		return val == rhs.val;
   }

	bool operator!=(const A& rhs) const
   {
		return val != rhs.val;
   }

   int val;
};

class TestHolder : public TESTCPP_NS::TestFixture
{
	void assertHolderEquals(const ValueHolder<A>& p1, const RefHolder<A>& p2)
	{
		TS_ASSERT(p1.getValue() == p2.getValue());
	}

	void assertHolderNotEquals(const ValueHolder<A>& p1, const RefHolder<A>& p2)
	{
		TS_ASSERT(p1.getValue() != p2.getValue());
	}

public:
	void setUp() { }
	void tearDown() { }

	/////////////////////////////////////////////////////////

	void testShouldBeAbleToCompareValueHolderAndRefHolder()
	{
		A a0(10);
		A a1(10);
		A a2(20);

		TS_ASSERT(ValueHolder<A>(a0).getValue() == RefHolder<A>(a1).getValue());
		TS_ASSERT(ValueHolder<A>(a0).getValue() != RefHolder<A>(a2).getValue());
		TS_ASSERT(ValueHolder<A>(a1).getValue() != RefHolder<A>(a2).getValue());
	}

	void testShouldBeAbleToConvertToHolderTypeAutomatically()
	{
		A a0(10);
		A a1(10);
		A a2(20);

		assertHolderEquals(a0, a1);
		assertHolderNotEquals(a0, a2);
		assertHolderNotEquals(a1, a2);
		assertHolderNotEquals(A(1), A(2));
		assertHolderEquals(A(1), A(1));
	}

	void testShouldBeAbleChangeTheValueOfRefHolder()
	{
		A a0(10);

		RefHolder<A> refHolder(a0);

		A& ref = const_cast<A&>(refHolder.getValue());

		ref.val = 20;

		TS_ASSERT(20 == a0.val);
	}

	void testShouldNotBeAbleChangeTheValueOfValueHolder()
	{
		A a0(10);

		ValueHolder<A> valHolder(a0);

		A& ref = const_cast<A&>(valHolder.getValue());

		ref.val = 20;

		TS_ASSERT_EQUALS(10, a0.val);
	}

};

