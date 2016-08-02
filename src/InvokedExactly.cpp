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

#include <mockcpp/OutputStringStream.h>
#include <mockcpp/InvokedExactly.h>
#include <mockcpp/Asserter.h>
#include <mockcpp/Formatter.h>

MOCKCPP_NS_START

/////////////////////////////////////////////////////////
InvokedExactly::InvokedExactly(const unsigned int times)
   : expectedInvokedTimes(times)
{
}

/////////////////////////////////////////////////////////
bool InvokedExactly::matches(const Invocation& inv) const
{

    return true;
}

/////////////////////////////////////////////////////////
std::string
InvokedExactly::toString(void) const
{
	 oss_t ss;

    ss << "exactly(" << expectedInvokedTimes << ")";

    return ss.str();
}

/////////////////////////////////////////////////////////
void InvokedExactly::verify(void)
{
	 oss_t oss;

    oss << "Expected invoking exactly " << expectedInvokedTimes 
        << " times, but it's actually invoked " << getInvokedTimes() 
        << " times.";

    MOCKCPP_ASSERT_TRUE_MESSAGE(
         oss.str(),
         getInvokedTimes() == expectedInvokedTimes );
}

MOCKCPP_NS_END


