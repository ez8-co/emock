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

#include <mockcpp/types/AnyBase.h>
#include <mockcpp/types/Holder.h>

MOCKCPP_NS_START

AnyBase::AnyBase() : content(0)
{}

AnyBase::AnyBase(PlaceHolder* holder)
    : content(holder)
{
}

AnyBase::~AnyBase()
{
   delete content;
}

bool AnyBase::empty() const
{
   return !content;
}

const std::type_info& AnyBase::type() const
{
   return content ? content->type() : typeid(void);
}

std::string AnyBase::toString() const
{
   return (content==0 ? std::string("void") : content->toString());
}

std::string AnyBase::toTypeString() const
{
   return (content==0 ? std::string("void") : content->toTypeString());
}

std::string AnyBase::toTypeAndValueString() const
{
   return (content==0 ? std::string("void") : content->toTypeAndValueString());
}

AnyBase& AnyBase::swap(AnyBase& rhs)
{
   PlaceHolder* temp = content;
   content = rhs.content;
   rhs.content = temp;
   return *this;
}

PlaceHolder* AnyBase::getContent() const
{
   return content;
}

MOCKCPP_NS_END

