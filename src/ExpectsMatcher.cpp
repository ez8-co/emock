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

#include <mockcpp/ExpectsMatcher.h>
#include <mockcpp/Invocation.h>

MOCKCPP_NS_START

ExpectsMatcher::ExpectsMatcher(Matcher* expectedMatcher)
   : matcher(expectedMatcher)
{
}

///////////////////////////////////////////////////////////
ExpectsMatcher::~ExpectsMatcher()
{
    delete matcher;
}

///////////////////////////////////////////////////////////
bool ExpectsMatcher::matches(const Invocation& inv) const 
{
    return matcher->matches(inv);
}

///////////////////////////////////////////////////////////
void ExpectsMatcher::increaseInvoked(const Invocation& inv)
{
    matcher->increaseInvoked(inv);
}

///////////////////////////////////////////////////////////
void ExpectsMatcher::verify()
{
    matcher->verify();
}

///////////////////////////////////////////////////////////
std::string ExpectsMatcher::toString() const
{
    oss_t oss;

    oss << ".expects(" << matcher->toString() << ")";

    return oss.str();
}

///////////////////////////////////////////////////////////

MOCKCPP_NS_END

