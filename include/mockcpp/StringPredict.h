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

#ifndef __MOCKCPP_STRING_PREDICT_H
#define __MOCKCPP_STRING_PREDICT_H

#include <string>
#include <mockcpp/Constraint.h>

MOCKCPP_NS_START

struct StringPredict
{
   virtual bool predict(const std::string& input, const std::string& target) const = 0;
   virtual std::string toString(const std::string& target) const = 0;

   virtual ~StringPredict() {}
};

MOCKCPP_NS_END

#endif


