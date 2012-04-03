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

#include <mockcpp/InvokedOnce.h>
#include <mockcpp/Asserter.h>
#include <mockcpp/OutputStringStream.h>

MOCKCPP_NS_START

///////////////////////////////////////////////////////
InvokedOnce::InvokedOnce()
{
}

///////////////////////////////////////////////////////
bool InvokedOnce::matches(const Invocation& inv) const
{
    return true;
}

///////////////////////////////////////////////////////
void InvokedOnce::increaseInvoked(const Invocation& inv)
{
    oss_t oss;

    oss << "Invocation is expected only once(), but you are trying to "
        << "invoke more than that";

    MOCKCPP_ASSERT_TRUE_MESSAGE(
         oss.str(), getInvokedTimes() < 1);
   
}
///////////////////////////////////////////////////////
std::string
InvokedOnce::toString(void) const
{
    return "once()";
}

///////////////////////////////////////////////////////
void InvokedOnce::verify(void)
{
    oss_t oss;

    oss << "Invocation is expected only once(), but it's been invoked "
        << getInvokedTimes() << " times";

    MOCKCPP_ASSERT_TRUE_MESSAGE(
         oss.str(), getInvokedTimes() == 1);
}

MOCKCPP_NS_END


