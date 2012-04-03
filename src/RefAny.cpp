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

#include <mockcpp/types/RefAny.h>

MOCKCPP_NS_START

RefAny::RefAny() {}

#if 0
RefAny::RefAny(const char* value)
      : AnyBase(new RefHolder<const char*>(value))
{
}

RefAny::RefAny(char* value)
      : AnyBase(new RefHolder<char*>(value))
{
}

#endif

RefAny::RefAny(const RefAny & other)
      : AnyBase(other.getContent() ? other.getContent()->clone() : 0)
{
}

RefAny& RefAny::operator=(const RefAny & rhs)
{
   RefAny(rhs).swap(*this);
   return *this;
}

RefAny& getEmptyRefAny()
{
    return const_cast<RefAny&>(EmptyRefAny);
}
/////////////////////////////////////////////////////

MOCKCPP_NS_END

