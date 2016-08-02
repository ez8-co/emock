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

#ifndef __MOCKCPP_ARGUMENTS_MATCH_BUILDER_H
#define __MOCKCPP_ARGUMENTS_MATCH_BUILDER_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/IsAnythingHelper.h>
#include <mockcpp/DummyBuilder.h>

MOCKCPP_NS_START

struct InvocationMocker;
struct Constraint;

template <typename Builder = DummyBuilder >
struct ArgumentsMatchBuilder : public Builder
{

    Builder& with( const Any& c01 = any()
                 , const Any& c02 = any()
                 , const Any& c03 = any()
                 , const Any& c04 = any()
                 , const Any& c05 = any()
                 , const Any& c06 = any()
                 , const Any& c07 = any()
                 , const Any& c08 = any()
                 , const Any& c09 = any()
                 , const Any& c10 = any()
                 , const Any& c11 = any()
                 , const Any& c12 = any()
    );

    Builder& which(unsigned int which1, const Any& c);

    virtual ~ArgumentsMatchBuilder() {}

private:

    virtual InvocationMocker* getMocker() const = 0;

};

MOCKCPP_NS_END

#include <mockcpp/ArgumentsMatchBuilder.tcc>

#endif

