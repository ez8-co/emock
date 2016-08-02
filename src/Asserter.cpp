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

#include <mockcpp/Asserter.h>
#include <string.h>

MOCKCPP_NS_START

void
assertTrue(unsigned srcline, const char* srcfile
			, const std::string &message, bool condition)
{
  if (!condition)
  {
    fail(srcline, srcfile, message);
  }
}

void
assertTrue(unsigned srcline, const char* srcfile, bool condition)
{
	assertTrue(srcline, srcfile, "", condition);
}

void
assertFalse(unsigned srcline, const char* srcfile, 
			const std::string &message , bool condition)
{
	assertTrue(srcline, srcfile, message, !condition);
}

void
assertFalse(unsigned srcline, const char* srcfile, bool condition)
{
	assertFalse(srcline, srcfile, "", condition);
}

void
fail(unsigned srcline, const char* srcfile, const std::string &message)
{
	assertionFailed(srcline, srcfile, message);
}

void
fail(unsigned srcline, const char* srcfile)
{
	assertionFailed(srcline, srcfile, "");
}

void
assertEquals(unsigned srcline, const char* srcfile,
                  const std::string& message,
                  const char *expected, const char *actual)
{
	if (::strcmp(expected, actual) != 0)
		fail(srcline, srcfile, message);
}

void
assertEquals(unsigned srcline, const char* srcfile,
                  const char *expected, const char *actual)
{
	assertEquals(srcline, srcfile, "", expected, actual);
}


MOCKCPP_NS_END


