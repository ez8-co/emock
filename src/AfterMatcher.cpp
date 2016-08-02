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

#include <mockcpp/AfterMatcher.h>
#include <mockcpp/InvocationMocker.h>
#include <mockcpp/Asserter.h>
#include <mockcpp/Invocation.h>
#include <mockcpp/InvocationId.h>
#include <mockcpp/ChainableMockMethodCore.h>

MOCKCPP_NS_START

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

    MOCKCPP_ASSERT_TRUE_MESSAGE(
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

MOCKCPP_NS_END

