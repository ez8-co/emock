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

#include <stdlib.h>

#include <mockcpp/DieStub.h>


MOCKCPP_NS_START

/////////////////////////////////////////////////
DieStub::DieStub(int exitCode)
   : code(exitCode)
{
}

/////////////////////////////////////////////////
bool DieStub::isCompleted() const
{
	return false;
}

/////////////////////////////////////////////////
Any& DieStub::invoke(void)
{
   ::exit(code);

   return getEmptyAny();
}

/////////////////////////////////////////////////
std::string DieStub::toString() const
{
   oss_t oss;

   oss << "die(" << code << ")";

   return oss.str();
}

/////////////////////////////////////////////////
const std::type_info& DieStub::type() const
{
   return typeid(void);
}

MOCKCPP_NS_END

