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


