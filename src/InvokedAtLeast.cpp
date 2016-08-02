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
#include <mockcpp/InvokedAtLeast.h>
#include <mockcpp/Asserter.h>
#include <mockcpp/Formatter.h>

MOCKCPP_NS_START

///////////////////////////////////////////////////////
InvokedAtLeast::InvokedAtLeast(const unsigned int times)
   : lowLimit(times)
{
}

///////////////////////////////////////////////////////
bool InvokedAtLeast::matches(const Invocation& inv) const
{
	return true;
}

///////////////////////////////////////////////////////
std::string InvokedAtLeast::toString(void) const
{
    oss_t oss;

    oss << "atLeast(" << lowLimit << ")";

    return oss.str();
}

///////////////////////////////////////////////////////
void InvokedAtLeast::verify(void)
{
    oss_t oss;

    oss << "Expected at least " << lowLimit
        << " times, but it's actually invoked " << getInvokedTimes() << " times";

    MOCKCPP_ASSERT_TRUE_MESSAGE(
			"Invoked too few times" 
         , getInvokedTimes() >= lowLimit);
}

MOCKCPP_NS_END


