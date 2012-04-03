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

USING_TESTNGPP_NS
USING_MOCKCPP_NS

FIXTURE(TestStaticMemberMocker, mock static member function)
{
    struct CUT
    {
        static int func()
        {
            return 11;
        }
    };

    TEST(static member function mocker test)
    {
        MOCKER(CUT::func)
            .stubs()
            .will(returnValue(100));
        ASSERT_EQ(100, CUT::func());
        GlobalMockObject::verify();
    }
};
