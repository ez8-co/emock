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

#ifndef __MOCKCPP_INVOCATION_MOCKER_H
#define __MOCKCPP_INVOCATION_MOCKER_H

#include <mockcpp/mockcpp.h>

#include <mockcpp/SelfDescribe.h>

MOCKCPP_NS_START

struct Method;
struct Matcher;
struct Stub;
struct InvocationMockerImpl;
struct Invocation;
struct InvocationId;
struct Any;

struct InvocationMocker : public SelfDescribe
{
    InvocationMocker(Method* core);
    ~InvocationMocker();

    Method* getMethod() const;
    void addStub(Stub* stub);
    void addMatcher(Matcher* matcher);
    bool hasBeenInvoked(void) const ;

    void setId(InvocationId* id);
    const InvocationId* const getId(void) const;

    bool matches(const Invocation& inv) const;
    Any& invoke(const Invocation& inv);

    void verify();

    std::string toString() const;

private:
    InvocationMockerImpl* This;
};

MOCKCPP_NS_END

#endif

