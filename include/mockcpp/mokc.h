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

#ifndef __MOCKCPP_MOKC_H
#define __MOCKCPP_MOKC_H

#ifdef __cplusplus
#  include <mockcpp/ChainingMockHelper.h>
#  include <mockcpp/ProcStub.h>

#  if defined(MOCKCPP_USE_MOCKABLE) 
#    include <mockcpp/Functor.h>
#    define MOCKER(api) MOCKCPP_NS::GlobalMockObject::instance.method(#api)
#  else
#    include <mockcpp/ApiHookMocker.h>
#    define MOCKER(api) MOCKCPP_NS::mockAPI(#api, api)
#  endif

USING_MOCKCPP_NS

#endif

#endif

