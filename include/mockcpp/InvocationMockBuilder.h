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

#ifndef __MOCKCPP_INVOCATION_MOCK_BUILDER_H
#define __MOCKCPP_INVOCATION_MOCK_BUILDER_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/DummyBuilder.h>

MOCKCPP_NS_START

struct InvocationMocker;

template <typename Builder = DummyBuilder>
struct InvocationMockBuilder : public Builder
{
   InvocationMockBuilder(InvocationMocker* mocker);

private:
   virtual InvocationMocker* getMocker() const;

private:
   InvocationMocker* invocationMocker;
};

MOCKCPP_NS_END

#include <mockcpp/InvocationMockBuilder.tcc>

#endif

