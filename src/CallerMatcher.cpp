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

#include <mockcpp/OutputStringStream.h>
#include <mockcpp/CallerMatcher.h>
#include <mockcpp/Invocation.h>

MOCKCPP_NS_START

///////////////////////////////////////////////////////////
CallerMatcher::CallerMatcher(const std::string& name)
    : nameOfCaller(name)
{
}

///////////////////////////////////////////////////////////
bool CallerMatcher::matches(const Invocation& inv) const 
{
    return inv.getNameOfCaller() == nameOfCaller;
}

///////////////////////////////////////////////////////////
void CallerMatcher::increaseInvoked(const Invocation& inv)
{
}

///////////////////////////////////////////////////////////
void CallerMatcher::verify()
{
}

///////////////////////////////////////////////////////////
std::string CallerMatcher::toString() const
{
    oss_t oss;

    oss << ".caller(" << nameOfCaller << ")";

    return oss.str();
}

MOCKCPP_NS_END

