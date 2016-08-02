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

#include <mockcpp/types/Any.h>
#include <mockcpp/types/AnyCast.h>

#include <mockcpp/Void.h>
#include <mockcpp/OutputStringStream.h>
#include <mockcpp/VoidResultHandler.h>
#include <mockcpp/SelfDescribe.h>
#include <mockcpp/Asserter.h>

MOCKCPP_NS_START

/////////////////////////////////////////////////////////
VoidResultHandler::VoidResultHandler(
                   const std::type_info& typeInfo
                 , const std::string& typeString
                 , const SelfDescribe* selfDescriber)
           : expectedTypeInfo(typeInfo)
           , expectedTypeString(typeString)
           , resultProvider(selfDescriber)
{
}

/////////////////////////////////////////////////////////
bool VoidResultHandler::matches(const Any& result) const
{
    return expectedTypeInfo != typeid(void) && any_castable<Void>(result);
}

/////////////////////////////////////////////////////////
const Any& VoidResultHandler::getResult(const Any& result) const
{
    oss_t oss;

    oss << "You need to specify a return value by using will(...) in \n"
        << resultProvider->toString() << "\n"
        << "Expected Return Type: " << expectedTypeString << "\n";

    MOCKCPP_FAIL(oss.str());

    return getEmptyAny();
}

/////////////////////////////////////////////////////////

MOCKCPP_NS_END

