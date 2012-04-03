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

#include <mockcpp/OutBoundPointer.h>
#include <mockcpp/Formatter.h>
#include <mockcpp/Asserter.h>

MOCKCPP_NS_START

////////////////////////////////////////////////////////////////////////////
void OutBoundPointerCheckConst(const std::string& typeString, bool isConst) 
{
   oss_t oss;

   oss << "A constant pointer " << typeString
       << " cannot be outbounded";

   MOCKCPP_ASSERT_FALSE_MESSAGE( oss.str(), isConst);
}

////////////////////////////////////////////////////////////////////////////
OutBoundPointer<void*>::OutBoundPointer(void* p, size_t size, Constraint* constraint)
	 : OutBoundPointerBase<void*>(p, size, constraint)
{
	MOCKCPP_ASSERT_TRUE_MESSAGE(
            "parameter \"size\" of OutBoundPointer<void*> cannot be specified as 0",
            size > 0);
}

////////////////////////////////////////////////////////////////////////////

MOCKCPP_NS_END

