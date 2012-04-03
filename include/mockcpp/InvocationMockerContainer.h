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

#ifndef __MOCKPP_INVOCATION_MOCKER_CONTAINER_H
#define __MOCKPP_INVOCATION_MOCKER_CONTAINER_H

#include <mockcpp/mockcpp.h>

#include <string>

MOCKCPP_NS_START

struct InvocationMocker;

struct InvocationMockerContainer
{
   virtual void addInvocationMocker(InvocationMocker* mocker) = 0;
   virtual void addDefaultInvocationMocker(InvocationMocker* mocker) = 0;
   virtual InvocationMocker* getInvocationMocker(const std::string& id) = 0;

   virtual ~InvocationMockerContainer() {}
};


MOCKCPP_NS_END


#endif 

