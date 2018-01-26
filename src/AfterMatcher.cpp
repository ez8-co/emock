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

#include <emock/AfterMatcher.h>
#include <emock/InvocationMocker.h>
#include <emock/Asserter.h>
#include <emock/Invocation.h>
#include <emock/InvocationId.h>
#include <emock/ChainableMockMethodCore.h>

EMOCK_NS_START

//////////////////////////////////////////////////////
AfterMatcher::AfterMatcher()
    : previousCall(0)
{}
//////////////////////////////////////////////////////
bool AfterMatcher::matches(const Invocation& inv) const
{
    return true;
}

//////////////////////////////////////////////////////
void AfterMatcher::increaseInvoked(const Invocation& inv)
{
    oss_t oss;

    oss << "Expected invoked after the invocation with id \""
        << previousCall->getId()->getId()
        << "\", but that invocation has NOT been invoked yet.";

    EMOCK_ASSERT_TRUE_MESSAGE(
         oss.str(), 
         previousCall->hasBeenInvoked());
}

//////////////////////////////////////////////////////
std::string AfterMatcher::toString() const
{
    return "after";
}

//////////////////////////////////////////////////////
void AfterMatcher::verify() 
{
}

//////////////////////////////////////////////////////
bool AfterMatcher::isCompleted(void) const
{
    return previousCall != 0;
}

//////////////////////////////////////////////////////
void AfterMatcher::setOrderingInvocationMocker(InvocationMocker* mocker)
{
    previousCall = mocker;
}

EMOCK_NS_END

