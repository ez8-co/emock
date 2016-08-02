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

