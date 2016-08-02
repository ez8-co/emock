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

#ifndef __MOCKCPP_SPY_H
#define __MOCKCPP_SPY_H

#include <string>
#include <mockcpp/types/RefAny.h>

MOCKCPP_NS_START

struct RefAny;

template <typename T>
struct Spy : public Constraint
{
    Spy(T& reference)
       : ref(reference)
    {}

    bool eval(const RefAny& inv) const
    {
         if(!any_castable<T>(inv)) return false;
         ref = any_cast<T>(inv);
         return true;
    }

    std::string toString() const
    {
        return "spy(" + toTypeAndValueString(ref) + ")";
    }

private:
    T& ref;
};

MOCKCPP_NS_END

#endif

