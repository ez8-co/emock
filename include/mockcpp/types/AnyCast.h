/***
   mockcpp is a C/C++ mock framework.
   Copyright [2008] [Darwin Yuan <darwin.yuan@gmail.com>]

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
***/

#ifndef __MOCKPP_ANY_CAST_H
#define __MOCKPP_ANY_CAST_H

#include <mockcpp/mockcpp.h>

#include <mockcpp/types/AnyBase.h>
#include <mockcpp/TypeTraits.h>
#include <mockcpp/Ignore.h>

#include <assert.h>
#define MOCKCPP_ASSERT(expr) assert(expr)

MOCKCPP_NS_START

/////////////////////////////////////////////////////////////////

template<typename ValueType>
ValueType *__ignore_type_any_cast(AnyBase *operand)
{
   static char buf[sizeof(ValueType)] = {0};
   return operand->type() == typeid(Ignore) ? reinterpret_cast<ValueType *>(buf) : 0;
}

template<typename ValueType>
ValueType* __type_any_cast(AnyBase *operand)
{
   typedef typename TypeTraits<ValueType>::Type nonref;
   typedef Holder<nonref> holder;

   if (operand->type() != typeid(ValueType))
   {
	   return 0;
   }

   holder* p = dynamic_cast<holder*>(operand->getContent());
   return p ? &const_cast<ValueType&>(p->getValue()) : 0;
}

template <typename ValueType>
ValueType* __any_cast(AnyBase* operand)
{
   if (operand == 0)
   {
      return 0;
   }

   ValueType *p = __type_any_cast<ValueType>(operand);

   return p ? p : __ignore_type_any_cast<ValueType>(operand);
}

//////////////////////////////////////////////// /////////////////
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
   return AnyCast<ValueType, __is_enum(ValueType)>::cast(operand);
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


