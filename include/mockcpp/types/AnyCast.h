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

#ifndef __MOCKPP_ANY_CAST_H
#define __MOCKPP_ANY_CAST_H

#include <boost/type_traits/is_enum.hpp>

#include <mockcpp/mockcpp.h>

#include <mockcpp/types/AnyBase.h>
#include <mockcpp/TypeTraits.h>

#include <assert.h>
#define MOCKCPP_ASSERT(expr) assert(expr)

MOCKCPP_NS_START

/////////////////////////////////////////////////////////////////
template <typename ValueType>
ValueType* __any_cast(AnyBase* operand)
{
   typedef typename TypeTraits<ValueType>::Type nonref;
   typedef Holder<nonref> holder;

   if (operand == 0 || operand->type() != typeid(ValueType))
   {
      return 0;
   }

   holder* p = dynamic_cast<holder*>(operand->getContent());

   return p ? &const_cast<ValueType&>(p->getValue()) : 0;
}

/////////////////////////////////////////////////////////////////
template <typename ValueType, bool IsEnum>
struct AnyCast
{
   static ValueType* cast(AnyBase* operand)
   {
      return __any_cast<ValueType>(operand);
   }
};

/////////////////////////////////////////////////////////////////
template <typename ValueType>
struct AnyCast<ValueType, true>
{
   static ValueType* cast(AnyBase* operand)
   {
      ValueType* p = 0;
      ( p = __any_cast<ValueType>(operand)) || \
      ( p = (ValueType*)__any_cast<unsigned long>(operand)) || \
      ( p = (ValueType*)__any_cast<unsigned int>(operand)) || \
      ( p = (ValueType*)__any_cast<unsigned short>(operand)) || \
      ( p = (ValueType*)__any_cast<unsigned char>(operand)) || \
      ( p = (ValueType*)__any_cast<long>(operand)) || \
      ( p = (ValueType*)__any_cast<int>(operand)) || \
      ( p = (ValueType*)__any_cast<short>(operand)) || \
      ( p = (ValueType*)__any_cast<char>(operand)) ;
      return p;
   }
};

/////////////////////////////////////////////////////////////////
template <typename ValueType>
ValueType* any_cast(AnyBase* operand)
{
   return AnyCast<ValueType, boost::is_enum<ValueType>::value>::cast(operand);
}

/////////////////////////////////////////////////////////////////
template <>
char* any_cast<char>(AnyBase* op);

/////////////////////////////////////////////////////////////////
template <>
short* any_cast<short>(AnyBase* op);

/////////////////////////////////////////////////////////////////
template <>
int* any_cast<int>(AnyBase* op);

/////////////////////////////////////////////////////////////////
template <>
long* any_cast<long>(AnyBase* op);

/////////////////////////////////////////////////////////////////
template <>
unsigned char* any_cast<unsigned char>(AnyBase* op);

/////////////////////////////////////////////////////////////////
template <>
unsigned short* any_cast<unsigned short>(AnyBase* op);

/////////////////////////////////////////////////////////////////
template <>
unsigned int* any_cast<unsigned int>(AnyBase* op);

/////////////////////////////////////////////////////////////////
template <>
unsigned long* any_cast<unsigned long>(AnyBase* op);

/////////////////////////////////////////////////////////////////
template<typename ValueType>
const ValueType * any_cast(const AnyBase* operand)
{
   return any_cast<ValueType>(const_cast<AnyBase*>(operand));
}

/////////////////////////////////////////////////////////////////
template<typename ValueType>
ValueType any_cast(const AnyBase& operand)
{
   typedef typename TypeTraits<ValueType>::Type nonref;

   const nonref * result = any_cast<nonref>(&operand);
   MOCKCPP_ASSERT(result != 0);

   return *const_cast<nonref*>(result);
}

/////////////////////////////////////////////////////////////////
template<typename ValueType>
ValueType any_cast(AnyBase& operand)
{
   typedef typename TypeTraits<ValueType>::Type nonref;

   nonref * result = any_cast<nonref>(&operand);
   MOCKCPP_ASSERT(result != 0);

   return *result;
}

/////////////////////////////////////////////////////////////////
template <typename ValueType>
bool any_castable(const AnyBase& val)
{
   typedef typename TypeTraits<ValueType>::Type nonref;

    return (!val.empty()) && (any_cast<nonref>(&val) != 0);
}

/////////////////////////////////////////////////////////////////

MOCKCPP_NS_END

#endif 


