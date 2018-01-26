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

#ifndef __EMOCK_ASSERTER_H
#define __EMOCK_ASSERTER_H

#include <emock/emock.h>

#include <emock/AssertionFailedError.h>

EMOCK_NS_START

void assertTrue( unsigned srcline, const char* srcfile
					, const std::string &message, bool condition);

void assertTrue( unsigned srcline, const char* srcfile
					, bool condition);

void assertFalse(unsigned srcline, const char* srcfile
					, const std::string &message , bool condition);

void assertFalse(unsigned srcline, const char* srcfile
					, bool condition);

void fail(unsigned srcline, const char* srcfile,
          const std::string &message);

void fail(unsigned srcline, const char* srcfile);

void assertEquals(unsigned srcline, const char* srcfile,
                  const std::string& message,
                  const char *expected, const char *actual);

void assertEquals(unsigned srcline, const char* srcfile,
                  const char *expected, const char *actual);

#define EMOCK_ASSERT_EQUALS_MESSAGE(msg, a, b) EMOCK_NS::assertEquals(__LINE__, __FILE__, msg, a, b)
#define EMOCK_ASSERT_EQUALS(a, b)  EMOCK_NS::assertEquals(__LINE__, __FILE__, "invalid: " #a " == " #b, a, b)
#define EMOCK_ASSERT_TRUE_MESSAGE(msg, cond) EMOCK_NS::assertTrue(__LINE__, __FILE__, msg, cond)
#define EMOCK_ASSERT_FALSE_MESSAGE(msg, cond) EMOCK_NS::assertFalse(__LINE__, __FILE__, msg, cond)
#define EMOCK_FAIL(msg)  EMOCK_NS::fail(__LINE__, __FILE__, msg)

EMOCK_NS_END

#endif

