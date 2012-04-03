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

#ifndef __MOCKCPP_OUTBOUND_H
#define __MOCKCPP_OUTBOUND_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/DecoratedConstraint.h>
#include <mockcpp/Formatter.h>
#include <mockcpp/Asserter.h>
#include <mockcpp/IsRef.h>

MOCKCPP_NS_START

template <typename T>
struct OutBound : public DecoratedConstraint
{
    OutBound(const T& val, Constraint* constraint = 0)
      : ref(val), DecoratedConstraint(constraint)
    {}

    bool evalSelf(const RefAny& val) const
    {
      return const_cast<RefAny&>(val).changeValue(ref);
    }

    std::string getName() const
    {
      return "outBound";
    }

    std::string getTypeAndValueString() const
    {
      return MOCKCPP_NS::toTypeAndValueString(ref);
    }

private:

    T ref;
};

MOCKCPP_NS_END

#endif

