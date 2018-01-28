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

struct Interface
{
    virtual int method() = 0;
    static int func() { return 0; }
    virtual ~Interface(){}
};

int func_stub()
{
    return 1000;
}

FIXTURE(emock_sample, emock samples)
{
    TEST(test_func_mocker)
    {
        EMOCK(Interface::func)
            .expects(once())
            .will(returnValue(10));
        ASSERT_EQ(10, Interface::func());
        GlobalMockObject::verify();
    }
	
    TEST(test will invoke)
    {
        EMOCK(Interface::func)
            .expects(once())
            .will(invoke(func_stub));
        ASSERT_EQ(1000, Interface::func());
        GlobalMockObject::verify();
    }	
};
