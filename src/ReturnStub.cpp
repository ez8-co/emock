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

#include <mockcpp/ReturnStub.h>

MOCKCPP_NS_START

/////////////////////////////////////////////////////
ReturnStub::ReturnStub(const Any& value)
		: returnValue(value), hasBeenInvoked(false)
{}

/////////////////////////////////////////////////////
bool ReturnStub::isCompleted() const
{
   return hasBeenInvoked;
}
/////////////////////////////////////////////////////
Any& ReturnStub::invoke(void)
{
    hasBeenInvoked = true;
    return returnValue;
}

/////////////////////////////////////////////////////
const std::type_info& ReturnStub::type() const
{
    return returnValue.type();
}

/////////////////////////////////////////////////////
std::string ReturnStub::toString(void) const
{
    return std::string("returnValue(") +
           returnValue.toTypeAndValueString() + 
           std::string(")");
}

MOCKCPP_NS_END

