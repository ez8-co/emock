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

#include <mockcpp/RepeatStub.h>
#include <mockcpp/Asserter.h>
#include <mockcpp/OutputStringStream.h>

MOCKCPP_NS_START

/////////////////////////////////////////////////////
RepeatStub::RepeatStub(const Any& value, unsigned int times)
		: returnValue(value), repeatedTimes(0), repeatTimes(times)
{}

/////////////////////////////////////////////////////
bool RepeatStub::isCompleted() const
{
   return repeatedTimes >= repeatTimes;
}

/////////////////////////////////////////////////////
Any& RepeatStub::invoke(void)
{
    oss_t oss;

    oss << "The repeat times ("
        << repeatTimes 
        << ") you specified has been reached";

    MOCKCPP_ASSERT_TRUE_MESSAGE(
       oss.str(),
       repeatedTimes < repeatTimes); 

    repeatedTimes++;

    return returnValue;
}

/////////////////////////////////////////////////////
const std::type_info& RepeatStub::type() const
{
    return returnValue.type();
}

/////////////////////////////////////////////////////
std::string RepeatStub::toString(void) const
{
    oss_t oss;

    oss << "repeat(" << returnValue.toTypeAndValueString() 
        << ", " << repeatTimes << ")";

    return oss.str();
}

MOCKCPP_NS_END

