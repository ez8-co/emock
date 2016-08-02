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

#include <inttypes.h>

#include "JmpOnlyApiHook.h"
#include <mockcpp/ApiHook.h>
#include <mockcpp/JmpCode.h>
#include <mockcpp/Asserter.h>

MOCKCPP_NS_START

////////////////////////////////////////////////////////
struct ApiHookImpl
{
   /////////////////////////////////////////////////////
   ApiHookImpl( const void* api
              , const void* stub )
       : stubHook(api, stub)
   {
   }

   /////////////////////////////////////////////////////
   JmpOnlyApiHook stubHook;
};

/////////////////////////////////////////////////////////////////
ApiHook::ApiHook 
              ( const void* api 
              , const void* stub )
	: This(new ApiHookImpl(api, stub))
{
}

/////////////////////////////////////////////////////////////////
ApiHook::~ApiHook()
{
	delete This;
}

/////////////////////////////////////////////////////////////////

MOCKCPP_NS_END

