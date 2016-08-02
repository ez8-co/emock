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

#include <mockcpp/ApiHookKey.h>
#include <mockcpp/ApiHook.h>
#include <mockcpp/ApiHookHolder.h>

MOCKCPP_NS_START

///////////////////////////////////////////////////////////
ApiHookKey::ApiHookKey(const void* api, ApiHookHolder* holder)
   : apiAddress(api)
   , hookHolder(holder)
{
   hook = new ApiHook(api, holder->getApiHook());
}

///////////////////////////////////////////////////////////
ApiHookKey::ApiHookKey(const void* api)
   : apiAddress(api), hook(0), hookHolder(0)
{
}

////////////////////////////////////////////////////////////
ApiHookKey::~ApiHookKey()
{
   delete hook;
   delete hookHolder;
}   

////////////////////////////////////////////////////////////
bool ApiHookKey::equals(
      const ChainableMockMethodKey* const rhs) const
{
    if(rhs == 0)
    {
       return false;
    }

    if(this == rhs)
    {
       return true;
    }

    ApiHookKey* key = \
          dynamic_cast<ApiHookKey*> \
             (const_cast<ChainableMockMethodKey*>(rhs));
    if(key == 0)
    {
       return false;
    }
     
    return key->apiAddress == this->apiAddress;
}

MOCKCPP_NS_END
