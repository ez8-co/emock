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

#ifndef __MOCKPP_ANY_H
#define __MOCKPP_ANY_H

#include <mockcpp/types/AnyBase.h>

#include <mockcpp/types/ValueHolder.h>
#include <mockcpp/Void.h>

MOCKCPP_NS_START

struct Any : public AnyBase
{
   Any();

   template <typename ValueType>
   Any(const ValueType& value)
      : AnyBase(new ValueHolder<ValueType>(value))
   {}

#if 0
   Any(const char* value);
#endif
   
   Any(const Any & other);

public:

   template<typename ValueType>
   Any& operator=(const ValueType & rhs)
   {
      Any(rhs).swap(*this);
      return *this;
   }

   Any& operator=(const Any & rhs);

   Constraint* getConstraint() const
   { return getContent()->getConstraint(); }
};

/////////////////////////////////////////////////////////////////
const Any EmptyAny;

const Any VoidAny = Any(Void());

Any& getEmptyAny();
Any& getVoidAny();
bool isVoidAny(const Any& val);

/////////////////////////////////////////////////////////////////

MOCKCPP_NS_END


#endif // __MOCKPP_ANY_H


