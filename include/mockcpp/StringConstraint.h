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

#ifndef __MOCKCPP_STRING_CONSTRAINT_H
#define __MOCKCPP_STRING_CONSTRAINT_H

#include <string>
#include <mockcpp/Constraint.h>

MOCKCPP_NS_START

struct StringPredict;

struct StringConstraint: public Constraint
{
    StringConstraint(const std::string& s, StringPredict* pred);
    ~StringConstraint();

    bool eval(const RefAny& val) const;

    std::string toString() const;

private:
   std::string str;
   StringPredict* predict;
};

MOCKCPP_NS_END

#endif


