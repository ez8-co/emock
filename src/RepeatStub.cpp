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

#include <mockcpp/RepeatStub.h>
#include <mockcpp/Asserter.h>
#include <mockcpp/OutputStringStream.h>

MOCKCPP_NS_START

/////////////////////////////////////////////////////
RepeatStub::RepeatStub(const Any& value, unsigned int times)
		: returnValue(value), repeatedTimes(0), repeatTimes(times)
{}

/////////////////////////////////////////////////////
bool RepeatStub::isCompleted() const
{
   return repeatedTimes >= repeatTimes;
}

/////////////////////////////////////////////////////
Any& RepeatStub::invoke(void)
{
    oss_t oss;

    oss << "The repeat times ("
        << repeatTimes 
        << ") you specified has been reached";

    MOCKCPP_ASSERT_TRUE_MESSAGE(
       oss.str(),
       repeatedTimes < repeatTimes); 

    repeatedTimes++;

    return returnValue;
}

/////////////////////////////////////////////////////
const std::type_info& RepeatStub::type() const
{
    return returnValue.type();
}

/////////////////////////////////////////////////////
std::string RepeatStub::toString(void) const
{
    oss_t oss;

    oss << "repeat(" << returnValue.toTypeAndValueString() 
        << ", " << repeatTimes << ")";

    return oss.str();
}

MOCKCPP_NS_END

