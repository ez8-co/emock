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
#include <mockcpp/InvokedAtMost.h>
#include <mockcpp/Asserter.h>
#include <mockcpp/Formatter.h>

MOCKCPP_NS_START

InvokedAtMost::InvokedAtMost(const unsigned int times)
   : highLimit(times)
{
}

///////////////////////////////////////////////////////
bool InvokedAtMost::matches(const Invocation& inv) const
{
	return true;
}

///////////////////////////////////////////////////////
void InvokedAtMost::increaseInvoked(const Invocation& inv)
{
    oss_t oss;

    oss << "Expected at most " << highLimit 
        << " times, but you are trying to invoke more than that.";

    MOCKCPP_ASSERT_TRUE_MESSAGE(
         oss.str(), getInvokedTimes() < highLimit);
}

///////////////////////////////////////////////////////
std::string InvokedAtMost::toString(void) const
{
	 oss_t oss;

    oss << "atMost(" << highLimit << ")";

    return oss.str();
}

///////////////////////////////////////////////////////
void InvokedAtMost::verify(void)
{
// We won't need to verify it here, it was checked at runtime.
#if 0
    oss_t oss;
    
    oss << "Expected at most " << highLimit 
        << " times, but it's actually invoked " << getInvokedTimes() << " times";

    MOCKCPP_ASSERT_TRUE_MESSAGE(
			oss.str(),
         getInvokedTimes() <= highLimit);
#endif
}

MOCKCPP_NS_END


