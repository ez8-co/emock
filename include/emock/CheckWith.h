/***
   emock is a cross-platform easy-to-use C++ Mock Framework based on mockcpp.
   Copyright [2017] [ez8.co] [orca <orca.zhang@yahoo.com>]

   This library is released under the Apache License, Version 2.0.
   Please see LICENSE file or visit https://github.com/ez8-co/emock for details.
   
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

#ifndef __EMOCK_CHECK_WITH_H
#define __EMOCK_CHECK_WITH_H

#include <emock/types/AnyCast.h>
#include <emock/Constraint.h>
#include <emock/Formatter.h>

EMOCK_NS_START

template <typename T, typename Predict>
struct CheckWith : public Constraint
{
    CheckWith(Predict pred)
      : predict(pred)
    {}

    bool eval(const RefAny& val) const
    {
      if(!any_castable<T>(val)) return false;
      
      return predict(any_cast<T>(val));
    }

    std::string toString() const
    {
      return std::string("check(") + 
             EMOCK_NS::toTypeAndValueString(predict) +
             std::string(")");
    }

private:

    mutable Predict predict;
};

EMOCK_NS_END

#endif
