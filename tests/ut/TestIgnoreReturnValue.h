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

#include <testngpp/testngpp.hpp>
#include <mockcpp/mockcpp.hpp>

USING_TESTNGPP_NS
USING_MOCKCPP_NS

FIXTURE(TestIgnoreReturnValue)
{
	SETUP()
	{
	}

	TEARDOWN()
	{
		MOCKCPP_NS::GlobalMockObject::verify();
	}


    static int func_int()
    {
        return 100;
    }

    TEST(test_ignore_return_int_value)
    {
        MOCKER(func_int)
            .stubs()
            .will(ignoreReturnValue());

        ASSERT_EQ(0, func_int());
    }

    TEST(testreturn_int_value)
    {
        MOCKER(func_int)
            .stubs()
            .will(returnValue(1));

        ASSERT_EQ(1, func_int());
    }

    static double func_double()
    {
        return 100.0;
    }

    TEST(test_ignore_return_double_value)
    {
        MOCKER(func_double)
            .stubs()
            .will(ignoreReturnValue());

        ASSERT_EQ(0.0, func_double());
    }

    TEST(testreturn_double_value)
    {
        MOCKER(func_double)
            .stubs()
            .will(returnValue(1.0));

        ASSERT_EQ(1.0, func_double());
    }

    static char func_char()
    {
        return 100;
    }

    TEST(test_ignore_return_char_value)
    {
        MOCKER(func_char)
            .stubs()
            .will(ignoreReturnValue());

        ASSERT_EQ(0, func_char());
    }

    TEST(testreturn_char_value)
    {
        MOCKER(func_char)
            .stubs()
            .will(returnValue(1));

        ASSERT_EQ(1, func_char());
    }

    struct Obj
    {
        Obj(int value) : field(value)
        {
        }
        Obj(const Obj &rhs) : field(rhs.field)
        {
        }
        Obj &operator=(const Obj &rhs)
        {
            field = rhs.field;
            return *this;
        }
        bool operator!=(const Obj &rhs) const
        {
            return field != rhs.field;
        }
        bool operator==(const Obj &rhs) const
        {
            return !(*this != rhs);
        }
        int field;
    };

    static Obj func_obj()
    {
        return Obj(100);
    }

    TEST(test_ignore_return_obj_value)
    {
        MOCKER(func_obj)
            .stubs()
            .will(ignoreReturnValue());

        Obj obj(0);
        ASSERT_EQ(obj, func_obj());
    }

    TEST(testreturn_obj_value)
    {
        Obj obj(20);
        MOCKER(func_obj)
            .stubs()
            .will(returnValue(obj));

        ASSERT_EQ(obj, func_obj());
    }

    static void func_void()
    {
    }

    TEST(test_ignore_return_void_value)
    {
        MOCKER(func_void)
            .stubs()
            .will(ignoreReturnValue());

        func_void();
    }
};
