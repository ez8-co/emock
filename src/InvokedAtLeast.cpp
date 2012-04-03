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
#include <mockcpp/InvokedAtLeast.h>
#include <mockcpp/Asserter.h>
#include <mockcpp/Formatter.h>

MOCKCPP_NS_START

///////////////////////////////////////////////////////
InvokedAtLeast::InvokedAtLeast(const unsigned int times)
   : lowLimit(times)
{
}

///////////////////////////////////////////////////////
bool InvokedAtLeast::matches(const Invocation& inv) const
{
	return true;
}

///////////////////////////////////////////////////////
std::string InvokedAtLeast::toString(void) const
{
    oss_t oss;

    oss << "atLeast(" << lowLimit << ")";

    return oss.str();
}

///////////////////////////////////////////////////////
void InvokedAtLeast::verify(void)
{
    oss_t oss;

    oss << "Expected at least " << lowLimit
        << " times, but it's actually invoked " << getInvokedTimes() << " times";

    MOCKCPP_ASSERT_TRUE_MESSAGE(
			"Invoked too few times" 
         , getInvokedTimes() >= lowLimit);
}

MOCKCPP_NS_END


