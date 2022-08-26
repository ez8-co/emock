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


//..\..\build_testngpp\src\runner\Debug\testngpp-runner.exe
//$(TargetName) -L"..\..\build_testngpp\src\listeners\Debug" -l"testngppstdoutlistener -c -f"
//$(TargetDir)


//USING_TESTNGPP_NS
USING_EMOCK_NS

struct CUT;

int EMOCK_API normal_method(CUT*)
{
    return 100;
}

int EMOCK_API normal_method_1(CUT* , int)
{
    return 101;
}

int EMOCK_API normal_method_2(const CUT* , int)
{
    return 102;
}
    
static int static_method()
{
    return 103;
}

static int static_method_1(int a)
{
    return 104;
}

struct CUT
{
    int normal_method()
    {
        return 11;
    }
    
    int normal_method_1(int a)
    {
        return 11;
    }

    int normal_method_2(int a) const
    {
        return 11;
    }
    
    static int static_method()
    {
        return 12;
    }

    static int static_method_1(int a)
    {
        return 12;
    }
};

#if __APPLE__
#else
FIXTURE(TestNonvirtualMemberMocker, mock nonvirtual nonstatic member method)
{

    TEST(normal member method with no param mocked as global function)
    {
        EMOCK(&CUT::normal_method)
            .stubs()
            .will(returnValue(100));
        CUT cut;
        ASSERT_EQ(100, cut.normal_method());
        GlobalMockObject::verify();

        EMOCK(&CUT::normal_method)
            .stubs()
            .will(invoke(normal_method));
        ASSERT_EQ(100, cut.normal_method());
        GlobalMockObject::verify();
/*
        EMOCK("!{int}CUT::normal_method")
            .stubs()
            .will(returnValue(100));
        ASSERT_EQ(100, cut.normal_method());
        GlobalMockObject::verify();

        EMOCKX(int (EMOCK_API *)(CUT*), "CUT::normal_method")
            .stubs()
            .will(invoke(normal_method));
        ASSERT_EQ(100, cut.normal_method());
        GlobalMockObject::verify();*/
    }

    TEST(normal member method with one param mocked as global function)
    {
        // the param number of hook function is one more than the method mocked, 
        // because when call CUT.normal_method_1(2) occur, the this pointer is the first argument
        CUT cut;
        EMOCK(&CUT::normal_method_1)
            .stubs()
            .with(eq(&cut), eq(2))
            .will(returnValue(101));
        ASSERT_EQ(101, cut.normal_method_1(2));
        GlobalMockObject::verify();

        EMOCK(&CUT::normal_method_1)
            .stubs()
            .with(eq(&cut), eq(2))
            .will(invoke(normal_method_1));
        ASSERT_EQ(101, cut.normal_method_1(2));
        GlobalMockObject::verify();
/*
        EMOCK("!{int}CUT::normal_method_1")
            .stubs()
            .will(returnValue(102));
        ASSERT_EQ(102, cut.normal_method_1(2));
        GlobalMockObject::verify();

        EMOCKX(int (EMOCK_API *)(CUT*, int), "CUT::normal_method_1")
            .stubs()
            .will(invoke(normal_method_1));
        ASSERT_EQ(101, cut.normal_method_1(2));
        GlobalMockObject::verify();*/

        EMOCK(&CUT::normal_method_2)
            .stubs()
            .with(eq(const_cast<CUT const*>(&cut)), eq(2))
            .will(invoke(normal_method_2));
        ASSERT_EQ(102, cut.normal_method_2(2));
        GlobalMockObject::verify();
    }

    TEST(static member method mocked as global function)
    {
        EMOCK(CUT::static_method)
            .stubs()
            .will(returnValue(103));
        ASSERT_EQ(103, CUT::static_method());
        GlobalMockObject::verify();

        EMOCK(CUT::static_method)
            .stubs()
            .will(invoke(static_method));
        ASSERT_EQ(103, CUT::static_method());
        GlobalMockObject::verify();
/*
        EMOCK("{int}CUT::static_method")
            .stubs()
            .will(returnValue(103));
        ASSERT_EQ(103, CUT::static_method());
        GlobalMockObject::verify();

        EMOCK("CUT::static_method")
            .stubs()
            .will(invoke(static_method));
        ASSERT_EQ(103, CUT::static_method());
        GlobalMockObject::verify();*/
    }

    TEST(static member method with one param mocked as global function)
    {
        EMOCK(CUT::static_method_1)
            .stubs()
            .will(returnValue(104));
        ASSERT_EQ(104, CUT::static_method_1(1));
        GlobalMockObject::verify();

        EMOCK(CUT::static_method_1)
            .stubs()
            .will(invoke(static_method_1));
        ASSERT_EQ(104, CUT::static_method_1(1));
        GlobalMockObject::verify();
/*
        EMOCK("{int}CUT::static_method_1")
            .stubs()
            .will(returnValue(104));
        ASSERT_EQ(104, CUT::static_method_1(1));
        GlobalMockObject::verify();

        EMOCK("CUT::static_method_1")
            .stubs()
            .will(invoke(static_method_1));
        ASSERT_EQ(104, CUT::static_method_1(1));
        GlobalMockObject::verify();*/
    }
};

#endif
