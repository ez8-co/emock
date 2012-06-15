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

int func(int)
{
    return 11;
}
int func(double)
{
    return 11;
}

FIXTURE(TestOverloadMethodMocker, mock overload function)
{
    struct CUT
    {
        static int func(int)
        {
            return 11;
        }
        static int func(double)
        {
            return 11;
        }
        virtual ~CUT() {}  // virtual destructor must be defined when mock an interface
        virtual int bar(int)
        {
            return 11;
        }
        virtual int bar(double)
        {
            return 11;
        }
    };

    TEST(overload static method mocker test)
    {
        MOCKER((int (*) (int)) CUT::func)
            .stubs()
            .will(returnValue(100));
        ASSERT_EQ(100, CUT::func(0));
        GlobalMockObject::verify();
    }

    TEST(overload free function mocker test)
    {
        MOCKER((int (*) (int)) func)
            .stubs()
            .will(returnValue(100));
        ASSERT_EQ(100, func(0));
        GlobalMockObject::verify();
    }

    TEST(overload virtual method mocker test)
    {
        MockObject<CUT> mocker;
        MOCK_OVERLOAD_METHOD(mocker, int (CUT::*) (int), bar)
            .stubs()
            .will(returnValue(100));
        ASSERT_EQ(100, static_cast<CUT*>(mocker)->bar(0));
        mocker.verify();
    }
};
