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

#ifndef __MOCKPP_REF_ANY_H
#define __MOCKPP_REF_ANY_H

#include <mockcpp/types/AnyBase.h>
#include <mockcpp/types/RefHolder.h>

MOCKCPP_NS_START

struct RefAny : public AnyBase
{
   RefAny();

   template <typename ValueType>
   RefAny(const ValueType& value)
      : AnyBase(new RefHolder<ValueType>(value))
   {}

#if 0
   RefAny(const char* value);
   RefAny(char* value);
#endif

   RefAny(const RefAny & other);

public:

   template<typename ValueType>
   RefAny& operator=(const ValueType & rhs)
   {
      RefAny(rhs).swap(*this);
      return *this;
   }

   RefAny& operator=(const RefAny & rhs);

   template <typename ValueType>
   bool changeValue(const ValueType& val)
   {
      RefHolder<ValueType>* p = dynamic_cast<RefHolder<ValueType>*>(getContent());
      if (p == 0)
      {
         return false;
      }

      p->changeValue(val);

      return true;
   }
};

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
const RefAny EmptyRefAny;

RefAny& getEmptyRefAny();
/////////////////////////////////////////////////////

MOCKCPP_NS_END


#endif // __MOCKPP_REF_ANY_H


