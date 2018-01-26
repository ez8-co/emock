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

#ifndef __EMOCK_MOCK_BUILDER_H
#define __EMOCK_MOCK_BUILDER_H

#include <emock/emock.h>

#include <emock/InvocationMockBuilder.h>
#include <emock/CallerMatchBuilder.h>
#include <emock/BeforeMatchBuilder.h>
#include <emock/ArgumentsMatchBuilder.h>
#include <emock/AfterMatchBuilder.h>
#include <emock/StubBuilder.h>
#include <emock/IdentityBuilder.h>

EMOCK_NS_START

///////////////////////////////////////////////
typedef InvocationMockBuilder<
          CallerMatchBuilder<
           BeforeMatchBuilder<
            ArgumentsMatchBuilder<
             AfterMatchBuilder<
              StubBuilder< 
                IdentityBuilder
              >
             >
            >
           >
          >
         > MockBuilder;

///////////////////////////////////////////////

EMOCK_NS_END

#endif

