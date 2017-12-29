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
#include <mockcpp/mokc.h>

#include <mockcpp/mockcpp.hpp>


//..\..\build_testngpp\src\runner\Debug\testngpp-runner.exe
//$(TargetName) -L"..\..\build_testngpp\src\listeners\Debug" -l"testngppstdoutlistener -c -f"
//$(TargetDir)


//USING_TESTNGPP_NS
USING_MOCKCPP_NS

struct CUT;

#ifdef _MSC_VER
int normal_method()
#else
int normal_method(CUT*)
#endif
{
    return 100;
}

#ifdef _MSC_VER
int normal_method_1(int)
#else
int normal_method_1(CUT* , int)
#endif 
{
    return 101;
}
    
static int static_method()
{
    return 102;
}

static int static_method_1(int a)
{
    return 103;
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
    
    static int static_method()
    {
        return 12;
    }

    static int static_method_1(int a)
    {
        return 12;
    }
};

FIXTURE(TestNonvirtualMemberMocker, mock nonvirtual nonstatic member method)
{

    TEST(normal member method with no param mocked as global function)
    {
        MOCKER(&CUT::normal_method)
            .stubs()
            .will(returnValue(100));
        CUT cut;
        ASSERT_EQ(100, cut.normal_method());
        GlobalMockObject::verify();

        MOCKER(&CUT::normal_method)
            .stubs()
            .will(invoke(normal_method));
        ASSERT_EQ(100, cut.normal_method());
        GlobalMockObject::verify();
    }

    TEST(normal member method with one param mocked as global function)
    {
        // the param number of hook function is one more than the method mocked, 
        // because when call CUT.normal_method_1(2) occur, the this pointer is the first argument
        MOCKER(&CUT::normal_method_1)
            .stubs()
            .with(any(), eq(2))
            .will(returnValue(101));
        CUT cut;
        ASSERT_EQ(101, cut.normal_method_1(2));
        GlobalMockObject::verify();

        MOCKER(&CUT::normal_method_1)
            .stubs()
            .with(any(), eq(2))
            .will(invoke(normal_method_1));
        ASSERT_EQ(101, cut.normal_method_1(2));
        GlobalMockObject::verify();
    }

    TEST(static member method mocked as global function)
    {
        MOCKER(CUT::static_method)
            .stubs()
            .will(returnValue(102));
        ASSERT_EQ(102, CUT::static_method());
        GlobalMockObject::verify();

        MOCKER(CUT::static_method)
            .stubs()
            .will(invoke(static_method));
        ASSERT_EQ(102, CUT::static_method());
        GlobalMockObject::verify();
    }

    TEST(static member method with one param mocked as global function)
    {
        MOCKER(CUT::static_method_1)
            .stubs()
            .will(returnValue(103));
        ASSERT_EQ(103, CUT::static_method_1(1));
        GlobalMockObject::verify();

        MOCKER(CUT::static_method_1)
            .stubs()
            .will(invoke(static_method_1));
        ASSERT_EQ(103, CUT::static_method_1(1));
        GlobalMockObject::verify();
    }
};
