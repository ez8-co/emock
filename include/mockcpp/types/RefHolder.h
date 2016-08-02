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

#ifndef __MOCKPP_REFHOLDER_H
#define __MOCKPP_REFHOLDER_H

#include <mockcpp/types/Holder.h>

MOCKCPP_NS_START

template<typename ValueType>
struct RefHolder : public Holder<ValueType>
{
    RefHolder(const ValueType& value)
      : ref(value)
    {
    }

    PlaceHolder * clone() const
    { return new RefHolder(ref); }

    const ValueType& getValue() const
    {
      return ref;
    }

    void changeValue(const ValueType& val)
    {
      ValueType* addr = &const_cast<ValueType&>(ref);
      (*addr) = val;
    }

private:

    const ValueType& ref;
};

MOCKCPP_NS_END


#endif // __MOCKPP_REFHOLDER_H


