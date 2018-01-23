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

#ifndef __MOCKPP_VALUEHOLDER_H
#define __MOCKPP_VALUEHOLDER_H

#include <iostream>

#include <mockcpp/mockcpp.h>

#include <mockcpp/types/Holder.h>

#include <mockcpp/EqualityUtil.h>
#include <mockcpp/Formatter.h>
#include <mockcpp/IsEqual.h>
#include <mockcpp/Void.h>
#include <mockcpp/IsAnythingHelper.h>
#include <mockcpp/Ignore.h>

MOCKCPP_NS_START

namespace {

template <typename T>
Constraint* constraint(const T& value)
{
    return new IsEqual<T>(value);
}

Constraint* constraint(Constraint* c)
{
    return c == 0 ? any() : c;
}

Constraint* constraint(const Constraint* c)
{
    return constraint(const_cast<Constraint*>(c));
}

Constraint* constraint(const Void& v)
{
    return any();
}

}

template<typename ValueType>
struct ValueHolderBase : public Holder<ValueType>
{
    Constraint* getConstraint() const
    {
       return constraint(getValue());
    }

    virtual const ValueType& getValue() const = 0;
};

template<typename ValueType>
struct ValueHolder : public ValueHolderBase<ValueType>
{
    ValueHolder(const ValueType& value)
      : held(value)
    {
    }

    PlaceHolder * clone() const
    { return new ValueHolder(held); }

    const ValueType& getValue() const
    {
      return held;
    }

private:

    ValueType held;
};

///////////////////////////////////////////////

MOCKCPP_NS_END


#endif // __MOCKPP_VALUEHOLDER_H


