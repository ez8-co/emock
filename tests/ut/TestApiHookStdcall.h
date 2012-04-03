/***
    mockcpp is a generic C/C++ mock framework.
    Copyright (C) <2010>  <Darwin Yuan: darwin.yuan@gmail.com>
	                      <Chen Guodong: sinojelly@gmail.com>

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

#include <testngpp/testngpp.hpp>
#include <mockcpp/mokc.h>


USING_MOCKCPP_NS
USING_TESTNGPP_NS

int __stdcall func(int a, int b)
{
	return 0;
}

int __stdcall func2(int a)
{
	return 0;
}

FIXTURE(ApiHookStdcall)
{
	int a; //TODO: static const cause linux .so load failure.
	int b;
	int ret;

	SETUP()
	{
		a = 3;
		b = 5;
		ret = 10;
		MOCKER(func)
			.expects(once())
			.with(eq(a), eq(b))
			.will(returnValue(ret));
	}

	TEARDOWN()
	{
		GlobalMockObject::verify();
		GlobalMockObject::reset();
	}
	
	TEST(can mock stdcall C function)
	{
		ASSERT_EQ(ret, func(a, b));
	}

	TEST(should throw some exception when calling the mocked stdcall function with wrong parameter)
	{
		ASSERT_THROWS_ANYTHING(func(a, b + 1));
		ASSERT_THROWS_ANYTHING(GlobalMockObject::verify());
	}

	TEST(can mock two stdcall functions at the same time)
	{
		MOCKER(func2)
			.expects(once())
			.with(eq(500))
			.will(returnValue(20));

		ASSERT_EQ(ret, func(a, b));
		ASSERT_EQ(20, func2(500));
	}
};
