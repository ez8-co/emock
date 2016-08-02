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

#ifndef __MOCKCPP_REPORT_FAILURE_H
#define __MOCKCPP_REPORT_FAILURE_H

#include <string>
#include <mockcpp/mockcpp.h>

MOCKCPP_NS_START

void
reportFailure
      ( unsigned int       line
      , const char*        file
      , const std::string& message);

#define MOCKCPP_REPORT_FAILURE(msg) \
   MOCKCPP_NS::reportFailure(__LINE__, __FILE__, msg)

#define MOCKCPP_ASSERT_FALSE(msg, expr) do {\
   if(expr) { \
      MOCKCPP_REPORT_FAILURE(msg); \
   } \
} while(0)

#define MOCKCPP_ASSERT_TRUE(msg, expr) do {\
   if(!(expr)) { \
      MOCKCPP_REPORT_FAILURE(msg); \
   } \
} while(0)

MOCKCPP_NS_END

#endif

