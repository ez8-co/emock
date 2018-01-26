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

USING_EMOCK_NS
USING_TESTNGPP_NS

typedef struct
{
	int a;
	int b;
}STRUCT_T;

struct Interface
{
	virtual void method(STRUCT_T *p) = 0;
	virtual ~Interface(){}
};

void client(Interface *interface, STRUCT_T *para)
{
	interface->method(para);
}

bool is_the_second_member_2(STRUCT_T *p)
{
	if (p->b == 2)
	{
		return true;
	}
	return false;
}

bool modify_the_first_member_to_10(STRUCT_T *p)
{
	p->a = 10;
	return true;
}

