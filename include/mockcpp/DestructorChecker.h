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

#ifndef __MOCKCPP_DESTRUCTOR_CHECKER_H
#define __MOCKCPP_DESTRUCTOR_CHECKER_H

#include <algorithm>
#include <typeinfo>

#include <mockcpp/mockcpp.h>
#include <mockcpp/MethodIndiceChecker.h>
#include <mockcpp/ReportFailure.h>

MOCKCPP_NS_START

///////////////////////////////////////////////
template <typename Interface, typename Original>
std::pair<unsigned int, unsigned int> getIndexOfDestructor()
{
   MethodIndiceChecker* checker = createMethodIndiceChecker(typeid(Original));

   Interface* iface = (Original*) checker->getObject();

   delete iface;

   unsigned int vptrIndex = 0;
   unsigned int vtblIndex = 0;

   bool result = checker->getIndice(true, vptrIndex, vtblIndex);
   delete checker;

   MOCKCPP_ASSERT_TRUE("You are trying to mock an interface without virtual destructor", result); 

   return std::pair<unsigned int, unsigned int>
       (vptrIndex, vtblIndex);
};

///////////////////////////////////////////////

MOCKCPP_NS_END

#endif

