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

#ifndef __MOCKPP_HOLDER_H
#define __MOCKPP_HOLDER_H

#include <mockcpp/mockcpp.h>

#include <mockcpp/types/PlaceHolder.h>

#include <mockcpp/EqualityUtil.h>
#include <mockcpp/Formatter.h>
#include <mockcpp/Void.h>

MOCKCPP_NS_START

template<typename ValueType>
struct Holder : public PlaceHolder
{
    typedef ValueType  Type;

    const std::type_info & type() const
    {
      return typeid(ValueType) == typeid(Void) ? typeid(void) : typeid(ValueType);
    }

    std::string toString() const
    {
       return MOCKCPP_NS::toString(getValue());
    }

    std::string toTypeString() const
    {
       return TypeString<ValueType>::value();
    }

    std::string toTypeAndValueString() const
    {
       return MOCKCPP_NS::toTypeAndValueString(getValue());
    }

    virtual const ValueType& getValue() const = 0;
};

MOCKCPP_NS_END


#endif // __MOCKPP_VALUEHOLDER_H


