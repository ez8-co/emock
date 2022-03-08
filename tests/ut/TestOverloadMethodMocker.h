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

#include <testngpp/testngpp.hpp>
#include <emock/emock.hpp>

USING_TESTNGPP_NS
USING_EMOCK_NS

int func(int)
{
    return 11;
}
double func(double)
{
    return 11;
}

#if __APPLE__
#else
FIXTURE(TestOverloadMethodMocker, mock overload function)
{
    struct CUT
    {
        static int func(int)
        {
            return 11;
        }
        static double func(double)
        {
            return 11;
        }
        virtual int bar(int)
        {
            return 11;
        }
        virtual double bar(double)
        {
            return 11;
        }
    };

    TEST(overload static method mocker test)
    {
        EMOCK((int (*) (int)) CUT::func)
            .stubs()
            .will(returnValue(100));
        ASSERT_EQ(100, CUT::func(0));
        GlobalMockObject::verify();

        EMOCK((double (*) (double)) CUT::func)
            .stubs()
            .will(returnValue(101.0));
        ASSERT_EQ(101.0, CUT::func(0.0));
        GlobalMockObject::verify();
/*
        EMOCK("{int}*::CUT::func(int)")
            .stubs()
            .will(returnValue(100));
        ASSERT_EQ(100, CUT::func(0));
        GlobalMockObject::verify();

        EMOCK("{double}*::CUT::func(double)")
            .stubs()
            .will(returnValue(101.0));
        ASSERT_EQ(101.0, CUT::func(0.0));
        GlobalMockObject::verify();*/
    }

    TEST(overload free function mocker test)
    {
        CUT cut;
        EMOCK(static_cast<int (CUT::*) (int)>(&CUT::bar))
            .stubs()
            .will(returnValue(100));
        ASSERT_EQ(100, cut.bar(0));
        GlobalMockObject::verify();

        EMOCK(static_cast<double (CUT::*) (double)>(&CUT::bar))
            .stubs()
            .will(returnValue(101.0));
        ASSERT_EQ(101.0, cut.bar(0.0));
        GlobalMockObject::verify();
/*
        EMOCK("!{int}*::CUT::bar(int)")
            .stubs()
            .will(returnValue(100));
        ASSERT_EQ(100, cut.bar(0));
        GlobalMockObject::verify();

        EMOCK("!{double}*::CUT::bar(double)")
            .stubs()
            .will(returnValue(101.0));
        ASSERT_EQ(101.0, cut.bar(0.0));
        GlobalMockObject::verify();*/
    }
};
#endif
