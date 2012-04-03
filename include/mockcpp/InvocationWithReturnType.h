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

#ifndef __MOCKCPP_INVOCATION_WITH_RETURN_TYPE_H
#define __MOCKCPP_INVOCATION_WITH_RETURN_TYPE_H

#include <mockcpp/mockcpp.h>

#include <mockcpp/Invocation.h>

MOCKCPP_NS_START

template <typename RT>
struct InvocationWithReturnType : public Invocation
{
	InvocationWithReturnType(
               const RefAny& p1 = RefAny()
             , const RefAny& p2 = RefAny()
             , const RefAny& p3 = RefAny()
             , const RefAny& p4 = RefAny()
             , const RefAny& p5 = RefAny()
             , const RefAny& p6 = RefAny())
		: Invocation(p1, p2, p3, p4, p5, p6)
	{}

   std::string toString(void) const;

	bool matches(Stub* stub) const
	{
      return stub->type() == typeid(RT);
	}
};

MOCKCPP_NS_END

#endif

