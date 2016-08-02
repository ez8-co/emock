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

#include <mockcpp/mockcpp.h>
#include <mockcpp/PendingMatcher.h>
#include <mockcpp/InvocationMocker.h>
#include <mockcpp/OrderingMatcher.h>
#include <mockcpp/Invocation.h>
#include <mockcpp/InvocationMockerNamespace.h>
#include <mockcpp/Asserter.h>

#include <string>

MOCKCPP_NS_START

#define SETUP_ORDERING_MATCHER() do { \
	setUpOrderingMatcher(); \
	oss_t oss; \
	oss << "There isn't an expectation whose id is \"" \
		 << id << "\" in namespace " << scope->getName() \
       << ", which is from : \n" << mocker->toString(); \
	MOCKCPP_ASSERT_TRUE_MESSAGE(oss.str(), matcher->isCompleted()); \
} while(0)

/////////////////////////////////////////////////////////////////
PendingMatcher::PendingMatcher(OrderingMatcher* orderingMatcher
                 , InvocationMockerNamespace* ns
                 , const std::string& identity
                 , InvocationMocker* ThisMocker)
	: matcher(orderingMatcher)
   , scope(ns)
	, id(identity)
   , mocker(ThisMocker)
{
}

/////////////////////////////////////////////////////////////////
PendingMatcher::~PendingMatcher()
{
    delete matcher;
}

/////////////////////////////////////////////////////////////////
bool PendingMatcher::matches(const Invocation& inv) const
{
    SETUP_ORDERING_MATCHER();
    return matcher->matches(inv);
}

/////////////////////////////////////////////////////////////////
void PendingMatcher::increaseInvoked(const Invocation& inv)
{
    SETUP_ORDERING_MATCHER();
    return matcher->increaseInvoked(inv);
}

/////////////////////////////////////////////////////////////////
std::string PendingMatcher::toString() const
{
	oss_t oss;
	oss << "." << matcher->toString() 
       << "("
       << scope->getName() << ", "
       << "\"" << id << "\""
       << ")" ;

	return oss.str();
}

/////////////////////////////////////////////////////////////////
void PendingMatcher::verify()
{
    return matcher->verify();
}

/////////////////////////////////////////////////////////////////
void PendingMatcher::setUpOrderingMatcher() const
{
    if(matcher->isCompleted()) 
    {
      return;
    }

    InvocationMocker* mocker = scope->getInvocationMocker(id);
    if(mocker != 0) {
      matcher->setOrderingInvocationMocker(mocker);
    }
}

MOCKCPP_NS_END


