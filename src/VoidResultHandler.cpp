/***
    mockcpp is a generic C/C++ mock framework.
    Copyright (C) <2009>  <Darwin Yuan: darwin.yuan@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
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

