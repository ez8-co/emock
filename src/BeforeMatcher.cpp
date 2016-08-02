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

#include <mockcpp/BeforeMatcher.h>
#include <mockcpp/InvocationMocker.h>
#include <mockcpp/Asserter.h>
#include <mockcpp/Invocation.h>
#include <mockcpp/InvocationId.h>
#include <mockcpp/ChainableMockMethodCore.h>

MOCKCPP_NS_START

//////////////////////////////////////////////////////
BeforeMatcher::BeforeMatcher()
	: previousCall(0)
{}

//////////////////////////////////////////////////////
bool BeforeMatcher::matches(const Invocation& inv) const
{
    return true;
}

//////////////////////////////////////////////////////
void BeforeMatcher::increaseInvoked(const Invocation& inv)
{
    oss_t oss;

    oss << "Expected invoked before the invocation with id \"" 
        << previousCall->getId()->getId()
        << "\", but that invocation has been invoked.";

    MOCKCPP_ASSERT_TRUE_MESSAGE(
         oss.str(),
         !previousCall->hasBeenInvoked());
}

//////////////////////////////////////////////////////
std::string BeforeMatcher::toString() const
{
    return "before";
}

//////////////////////////////////////////////////////
void BeforeMatcher::verify() 
{
}

//////////////////////////////////////////////////////
bool BeforeMatcher::isCompleted(void) const
{
    return previousCall != 0;
}

//////////////////////////////////////////////////////
void BeforeMatcher::setOrderingInvocationMocker(InvocationMocker* mocker)
{
    previousCall = mocker;
}

MOCKCPP_NS_END

