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


