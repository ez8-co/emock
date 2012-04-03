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

// for linux define __cdecl to null
#if !defined(_MSC_VER) && !defined(__cdecl)
#define __cdecl
#endif

FIXTURE(TestNonvirtualMemberMocker, mock nonvirtual nonstatic member method)
{
    struct CUT
    {
        int normal_method() //__cdecl is optional, because it has no param
        {
            return 11;
        }
        
        int __cdecl  normal_method_1(int a) //__cdecl is must
        {
            return 11;
        }
        
        static int static_method()
        {
            return 12;
        }

        static int static_method_2(void *This, int a)
        {
            return 12;
        }
    };

    TEST(normal member method with no param mocked as global function)
    {
        GlobalMockObject::instance.method
            ( "CUT::normal_method"
            , getAddrOfMethod(&CUT::normal_method)
            , (const void *)CApiHookFunctor<BOOST_TYPEOF(CUT::static_method)>::hook
    		, ThunkCodeProvider<BOOST_TYPEOF(CUT::static_method)>()())
            .stubs()
            .will(returnValue(100));
        CUT cut;
        ASSERT_EQ(100, cut.normal_method());
        GlobalMockObject::verify();
    }

    TEST(normal member method with one param mocked as global function)
    {
        // the param number of hook function is one more than the method mocked, 
        // because when call CUT.normal_method_1(2) occur, the this pointer is the first argument
        GlobalMockObject::instance.method
            ( "CUT::normal_method_1"
            , getAddrOfMethod(&CUT::normal_method_1)
            , (const void *)CApiHookFunctor<BOOST_TYPEOF(CUT::static_method_2)>::hook
    		, ThunkCodeProvider<BOOST_TYPEOF(CUT::static_method_2)>()())
            .stubs()
            .with(any(), eq(2))
            .will(returnValue(101));
        CUT cut;
        ASSERT_EQ(101, cut.normal_method_1(2));
        GlobalMockObject::verify();
    }

    TEST(static member method mocked as global function)
    {
        MOCKER(CUT::static_method)
            .stubs()
            .will(returnValue(100));
        ASSERT_EQ(100, CUT::static_method());
        GlobalMockObject::verify();
    }
};
