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

#ifndef __MOCKCPP_MOCK_OBJECT_HELPER_H__
#define __MOCKCPP_MOCK_OBJECT_HELPER_H__

#include <mockcpp/mockcpp.h>
#include <mockcpp/MockObject.h>

#define METHOD(m) method(&m, #m)

#define MOCK_METHOD(obj, m) \
   obj.method_helper(&m, "", #m)

#define MOCK_OVERLOAD_METHOD(obj, type, m) \
   obj.method_helper((type)&m, "("#type")", #m)

#endif
