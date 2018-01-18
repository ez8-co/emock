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

#ifndef __MOCKPP_REF_ANY_H
#define __MOCKPP_REF_ANY_H

#include <mockcpp/types/AnyBase.h>
#include <mockcpp/types/RefHolder.h>
#include <stdarg.h>

MOCKCPP_NS_START

struct RefAny : public AnyBase
{
   RefAny();

#ifdef __GNUC__
   RefAny(va_list value)
      : AnyBase(new RefVaList())
   {
      reinterpret_cast<RefVaList*>(getContent())->changeValue(value);
   }
#endif

   template <typename ValueType>
   RefAny(const ValueType& value)
      : AnyBase(new RefHolder<ValueType>(value))
   {}


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


