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

#ifndef __EMOCK_INVOCATION_H
#define __EMOCK_INVOCATION_H

#include <string>

#include <emock/emock.h>

#include <emock/types/RefAny.h>

EMOCK_NS_START

struct Stub;
struct InvocationImpl;

struct Invocation
{
    Invocation(const std::string& nameOfCaller
             , const RefAny& p01 = RefAny()
             , const RefAny& p02 = RefAny()
             , const RefAny& p03 = RefAny()
             , const RefAny& p04 = RefAny()
             , const RefAny& p05 = RefAny()
             , const RefAny& p06 = RefAny()
             , const RefAny& p07 = RefAny()
             , const RefAny& p08 = RefAny()
             , const RefAny& p09 = RefAny()
             , const RefAny& p10 = RefAny()
             , const RefAny& p11 = RefAny()
             , const RefAny& p12 = RefAny()
    );

    virtual ~Invocation();

    RefAny& getParameter(const unsigned int i) const;

    std::string getNameOfCaller() const;

    std::string toString(void) const;

private:
    InvocationImpl* This;
};

EMOCK_NS_END

#endif

