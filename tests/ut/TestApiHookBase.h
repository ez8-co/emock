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

void vfunc0()
{
}

int func0()
{
    return 0;
}

void vfunc1(int a)
{
}

int func1(int a)
{
    return 0;
}

double ffunc1(double a)
{
	return a;
}

int func2(int a, int b)
{
    return 0;
}

double ffunc2(int a, double b)
{
	return b;
}

int func3(int a, int b, int c)
{
    return 0;
}

int func4(int a, int b, int c, int d)
{
    return 0;
}

int func5(int a, int b, int c, int d, int e)
{
    return 0;
}

int func6(int a, int b, int c, int d, int e, int f)
{
    return 0;
}

int func7(int a, int b, int c, int d, int e, int f, int g)
{
    return 0;
}

int func8(int a, int b, int c, int d, int e, int f, int g, int h)
{
    return 0;
}

int func9(int a, int b, int c, int d, int e, int f, int g, int h, int i)
{
    return 0;
}

int func10(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j)
{
    return 0;
}

int func11(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k)
{
    return 0;
}

int func12(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k, int l)
{
    return 0;
}

FIXTURE(ApiHookBase)
{
    int a; //TODO: static const cause linux .so load failure.
    int b;
    int c;
    int d;
    int e;
    int f;
    int g;
    int h;
    int i;
    int j;
    int k;
    int l;
    int ret;

    SETUP()
    {
        a = 1;
        b = 2;
        c = 3;
        d = 4;
        e = 5;
        f = 6;
        g = 7;
        h = 8;
        i = 9;
        j = 10;
        k = 11;
        l = 12;
        ret = 10;
    }

    TEARDOWN()
    {
        GlobalMockObject::verify();
    }

    TEST(can mock C function with no return and no parameter)
    {
        MOCKER(vfunc0)
            .expects(once());

        vfunc0();
    }

    TEST(can mock C function with return and no parameter)
    {
        MOCKER(func0)
            .expects(once())
            .will(returnValue(ret));

        ASSERT_EQ(ret, func0());
    }

    TEST(can mock C function with no return and one parameter)
    {
        MOCKER(vfunc1)
            .expects(once())
            .with(eq(a));

        vfunc1(a);
    }

    TEST(can mock C function with 1 parameter (int) & return (int))
    {
        MOCKER(func1)
            .expects(once())
            .with(eq(a))
            .will(returnValue(ret));

        ASSERT_EQ(ret, func1(a));
    }

	TEST(can mock c function with 1 parameter (double) & return (double))
	{
        MOCKER(ffunc1)
            .expects(once())
            .with(eq((double)1.0))
            .will(returnValue((double)1.0));

		ASSERT_EQ((double)1.0, ffunc1((double)1.0));
	}

    TEST(can mock C function with return and two parameters)
    {
        MOCKER(func2)
            .expects(once())
            .with(eq(a), eq(b))
            .will(returnValue(ret));

        ASSERT_EQ(ret, func2(a, b));
    }

	TEST(can mock c function with 2 parameter2 (double) & return (double))
	{
        MOCKER(ffunc2)
            .expects(once())
            .with(eq((int)2), eq((double)1.1))
            .will(returnValue((double)1.9));

		ASSERT_EQ((double)1.9, ffunc2(2, 1.1));
	}

    TEST(can mock C function with return and 3 parameters)
    {
        MOCKER(func3)
            .expects(once())
            .with(eq(a), eq(b), eq(c))
            .will(returnValue(ret));

        ASSERT_EQ(ret, func3(a, b, c));
    }

    TEST(can mock C function with return and 4 parameters)
    {
        MOCKER(func4)
            .expects(once())
            .with(eq(a), eq(b), eq(c), eq(d))
            .will(returnValue(ret));

        ASSERT_EQ(ret, func4(a, b, c, d));
    }

    TEST(can mock C function with return and 5 parameters)
    {
        MOCKER(func5)
            .expects(once())
            .with(eq(a), eq(b), eq(c), eq(d), eq(e))
            .will(returnValue(ret));

        ASSERT_EQ(ret, func5(a, b, c, d, e));
    }


    TEST(can mock C function with return and 6 parameters)
    {
        MOCKER(func6)
            .expects(once())
            .with(eq(a), eq(b), eq(c), eq(d), eq(e), eq(f))
            .will(returnValue(ret));

        ASSERT_EQ(ret, func6(a, b, c, d, e, f));
    }

    TEST(can mock C function with return and 7 parameters)
    {
        MOCKER(func7)
            .expects(once())
            .with(eq(a), eq(b), eq(c), eq(d), eq(e), eq(f), eq(g))
            .will(returnValue(ret));

        ASSERT_EQ(ret, func7(a, b, c, d, e, f, g));
    }

    TEST(can mock C function with return and 8 parameters)
    {
        MOCKER(func8)
            .expects(once())
            .with(eq(a), eq(b), eq(c), eq(d), eq(e), eq(f), eq(g), eq(h))
            .will(returnValue(ret));

        ASSERT_EQ(ret, func8(a, b, c, d, e, f, g, h));
    }

    TEST(can mock C function with return and 9 parameters)
    {
        MOCKER(func9)
            .expects(once())
            .with(eq(a), eq(b), eq(c), eq(d), eq(e), eq(f), eq(g), eq(h), eq(i))
            .will(returnValue(ret));

        ASSERT_EQ(ret, func9(a, b, c, d, e, f, g, h, i));
    }

    TEST(can mock C function with return and 10 parameters)
    {
        MOCKER(func10)
            .expects(once())
            .with(eq(a), eq(b), eq(c), eq(d), eq(e), eq(f), eq(g), eq(h), eq(i), eq(j))
            .will(returnValue(ret));

        ASSERT_EQ(ret, func10(a, b, c, d, e, f, g, h, i, j));
    }


    TEST(can mock C function with return and 11 parameters)
    {
        MOCKER(func11)
            .expects(once())
            .with(eq(a), eq(b), eq(c), eq(d), eq(e), eq(f), eq(g), eq(h), eq(i), eq(j), eq(k))
            .will(returnValue(ret));

        ASSERT_EQ(ret, func11(a, b, c, d, e, f, g, h, i, j, k));
    }

    TEST(can mock C function with return and 12 parameters)
    {
        MOCKER(func12)
            .expects(once())
            .with(eq(a), eq(b), eq(c), eq(d), eq(e), eq(f), eq(g), eq(h), eq(i), eq(j), eq(k), eq(l))
            .will(returnValue(ret));

        ASSERT_EQ(ret, func12(a, b, c, d, e, f, g, h, i, j, k, l));
    }
};


