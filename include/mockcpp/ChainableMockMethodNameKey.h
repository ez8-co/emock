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

#ifndef __MOCKCPP_CHAINABLE_MOCK_METHOD_NAME_KEY_H
#define __MOCKCPP_CHAINABLE_MOCK_METHOD_NAME_KEY_H

#include <mockcpp/mockcpp.h>

#include <mockcpp/ChainableMockMethodKey.h>

#include <string>

MOCKCPP_NS_START

struct ChainableMockMethodNameKey
    : public ChainableMockMethodKey
{
   ChainableMockMethodNameKey(const std::string& name);

   bool equals(const ChainableMockMethodKey * const rhs) const;

   std::string& getMethodName() const;

private:
   std::string methodName;
};

MOCKCPP_NS_END

#endif

