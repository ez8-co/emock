/***
   emock is a cross-platform easy-to-use C++ Mock Framework based on mockcpp.
   Copyright [2017] [ez8.co] [orca <orca.zhang@yahoo.com>]

   This library is released under the Apache License, Version 2.0.
   Please see LICENSE file or visit https://github.com/ez8-co/emock for details.

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
#include <emock/emock.hpp>
#include <stdarg.h>


USING_EMOCK_NS
USING_TESTNGPP_NS

int func(int a, int b)
{
    return 0;
}

int foo(int a, int b)
{
    return 0;
}

int func2(int a)
{
    return 0;
}

int var_func(int a, ...)
{
    return 0;
}

int var_func2(int a, int b, ...)
{
    return 0;
}

int va_list_func(int a, va_list arg)
{
    return 0;
}

int va_list_func2(int a, int b, va_list arg)
{
    return 0;
}

#ifdef _MSC_VER
void init_va_list(va_list *arg, ...)
{
    va_start(*arg, arg);
}
#endif

FIXTURE(ApiHook)
{
	int a; //TODO: static const cause linux .so load failure.
	int b;
	int ret;

	SETUP()
	{
		a = 3;
		b = 5;
		ret = 10;
		EMOCK(func)
			.expects(once())
			.with(eq(a), eq(b))
			.will(returnValue(ret));

	}

	TEARDOWN()
	{
		GlobalMockObject::verify();
		GlobalMockObject::reset();
	}

	TEST(can mock C function)
	{
		ASSERT_EQ(ret, func(a, b));
	}

	TEST(should throw some exception when calling the mocked function with wrong parameter)
	{
	    #ifdef _MSC_VER
		ASSERT_THROWS_ANYTHING(func(a, b + 1));
		ASSERT_THROWS_ANYTHING(GlobalMockObject::verify());
		#else
		// when using gnu compiler, can not process the exception in thunk code
		ASSERT_EQ(ret, func(a, b));
		#endif
	}

	TEST(can mock two functions at the same time)
	{
		EMOCK(func2)
			.expects(once())
			.with(eq(500))
			.will(returnValue(20));

		ASSERT_EQ(ret, func(a, b));
		ASSERT_EQ(20, func2(500));
	}

    TEST(can mock 2 functions which has same prototype)
    {
       EMOCK(foo).stubs().will(returnValue(20));
       ASSERT_EQ(ret, func(a, b));
       ASSERT_EQ(20,  foo(a, b));
    }

    TEST(can mock varadic functions)
    {
       EMOCK(var_func).stubs().will(returnValue(20));
       ASSERT_EQ(ret, func(a, b));
       ASSERT_EQ(20, var_func(a, b));
    }

    TEST(can mock varadic functions with 2 arg)
    {
       EMOCK(var_func2).stubs().will(returnValue(20));
       ASSERT_EQ(ret, func(a, b));
       ASSERT_EQ(20, var_func2(a, b, ret));
    }

#ifndef _MSC_VER
    TEST(can mock functions with va_list)
    {
       va_list arg;
#ifdef _MSC_VER
       init_va_list(&arg, arg);
#endif
       EMOCK(va_list_func).stubs().will(returnValue(20));
       ASSERT_EQ(ret, func(a, b));
       ASSERT_EQ(20, va_list_func(a, arg));
    }

    TEST(can mock functions with va_list arg 2)
    {
       va_list arg;
#ifdef _MSC_VER
       init_va_list(&arg, arg);
#endif
       EMOCK(va_list_func2).stubs().will(returnValue(20));
       ASSERT_EQ(ret, func(a, b));
       ASSERT_EQ(20, va_list_func2(a, b, arg));
    }
#endif
};
