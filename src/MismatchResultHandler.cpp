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

#include <mockcpp/MismatchResultHandler.h>
#include <mockcpp/SelfDescribe.h>
#include <mockcpp/Asserter.h>

MOCKCPP_NS_START

////////////////////////////////////////////////////////////////
MismatchResultHandler::MismatchResultHandler(
                           bool castable
                         , const std::type_info& info
                         , const std::string& typeString
                         , const SelfDescribe* selfDescriber)
           : isCastable(castable)
			  , expectedTypeInfo(info)
			  , expectedTypeString(typeString)
			  , resultProvider(selfDescriber)
{
}

////////////////////////////////////////////////////////////////
bool MismatchResultHandler::matches(const Any& result) const
{
      return !isCastable;
}

////////////////////////////////////////////////////////////////
const Any& MismatchResultHandler::getResult(const Any& result) const
{
    oss_t oss;

    oss << "Returned type does NOT match the method declaration \n"
        << "Required : " << expectedTypeString << "\n"
        << "Returned : " << result.toTypeString() << ", which is from\n"
        << resultProvider->toString();

    MOCKCPP_ASSERT_FALSE_MESSAGE(oss.str(), matches(result));

    return getEmptyAny();
}

MOCKCPP_NS_END

