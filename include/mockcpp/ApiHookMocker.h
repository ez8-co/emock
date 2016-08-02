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

#ifndef __MOCKCPP_API_HOOK_MOCKER_H__
#define __MOCKCPP_API_HOOK_MOCKER_H__

#include <mockcpp/mockcpp.h>
#include <mockcpp/GlobalMockObject.h>
#include <mockcpp/ApiHookHolderFactory.h>

MOCKCPP_NS_START

template <typename API>
InvocationMockBuilderGetter mockAPI(const std::string& name, API* api)
{
    return MOCKCPP_NS::GlobalMockObject::instance.method
                 ( name
                 , reinterpret_cast<const void*>(api)
                 , ApiHookHolderFactory::create(api));
}


MOCKCPP_NS_END

#endif

