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

#include <algorithm>
#include <typeinfo>

#include <mockcpp/mockcpp.h>
#include <mockcpp/MethodTypeTraits.h>
#include <mockcpp/MethodIndiceChecker.h>

MOCKCPP_NS_START

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////
template <typename Interface, typename Method>
std::pair<unsigned int, unsigned int>
getIndicesOfMethod(Method m)
{
   typedef typename MethodTypeTraits<Interface, Method>::MethodType ExpectedMethodType;
   ExpectedMethodType expectedMethod = m;

   typedef void (Interface::*Checker)(void*);

   Checker check = \
      reinterpret_cast<Checker>(expectedMethod);

   MethodIndiceChecker* checker = createMethodIndiceChecker(typeid(Interface));

   Interface* iface = (Interface*)checker->getObject();

   (iface->*check)(0);
   
   unsigned int vptrIndex = 0;
   unsigned int vtblIndex = 0;

   bool result = checker->getIndice(false, vptrIndex, vtblIndex);

   delete checker;

   MOCKCPP_ASSERT_TRUE("You are trying to mock a non-pure-virtual object", result); 

   return std::pair<unsigned int, unsigned int>
       (vptrIndex, vtblIndex);
};


///////////////////////////////////////////////////////////////////////

MOCKCPP_NS_END

