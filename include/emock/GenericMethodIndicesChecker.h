/***
   emock is a cross-platform easy-to-use C++ Mock Framework based on mockcpp.
   Copyright [2017] [ez8.co] [orca <orca.zhang@yahoo.com>]

   This library is released under the Apache License, Version 2.0.
   Please see LICENSE file or visit https://github.com/ez8-co/emock for details.
   
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

#include <algorithm>

#include <emock/emock.h>
#include <emock/MethodTypeTraits.h>
#include <emock/MethodIndiceChecker.h>

EMOCK_NS_START

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////
template <typename Interface, typename Method>
std::pair<unsigned int, unsigned int>
getIndicesOfMethod(Method m)
{
   typedef typename MethodTypeTraits<Interface, Method>::MethodType ExpectedMethodType;
   ExpectedMethodType expectedMethod = m;

   typedef void (Interface::*Checker)(void*);

   Checker check = reinterpret_cast<Checker>(expectedMethod);

   MethodIndiceChecker* checker = createMethodIndiceChecker(typeid(Interface));

   Interface* iface = (Interface*)checker->getObject();

   (iface->*check)(0);
   
   unsigned int vptrIndex = 0;
   unsigned int vtblIndex = 0;

   bool result = checker->getIndice(false, vptrIndex, vtblIndex);

   delete checker;

   EMOCK_ASSERT_TRUE("You are trying to mock a non-pure-virtual object, please use `MOCKER(&Class::method)` instead.", result); 

   return std::pair<unsigned int, unsigned int>
       (vptrIndex, vtblIndex);
}

///////////////////////////////////////////////////////////////////////

EMOCK_NS_END

