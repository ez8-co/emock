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
#include <mockcpp/InvokedAtMost.h>
#include <mockcpp/Asserter.h>
#include <mockcpp/Formatter.h>

MOCKCPP_NS_START

InvokedAtMost::InvokedAtMost(const unsigned int times)
   : highLimit(times)
{
}

///////////////////////////////////////////////////////
bool InvokedAtMost::matches(const Invocation& inv) const
{
	return true;
}

///////////////////////////////////////////////////////
void InvokedAtMost::increaseInvoked(const Invocation& inv)
{
    oss_t oss;

    oss << "Expected at most " << highLimit 
        << " times, but you are trying to invoke more than that.";

    MOCKCPP_ASSERT_TRUE_MESSAGE(
         oss.str(), getInvokedTimes() < highLimit);
}

///////////////////////////////////////////////////////
std::string InvokedAtMost::toString(void) const
{
	 oss_t oss;

    oss << "atMost(" << highLimit << ")";

    return oss.str();
}

///////////////////////////////////////////////////////
void InvokedAtMost::verify(void)
{
// We won't need to verify it here, it was checked at runtime.
#if 0
    oss_t oss;
    
    oss << "Expected at most " << highLimit 
        << " times, but it's actually invoked " << getInvokedTimes() << " times";

    MOCKCPP_ASSERT_TRUE_MESSAGE(
			oss.str(),
         getInvokedTimes() <= highLimit);
#endif
}

MOCKCPP_NS_END


