/***
    mockcpp is a generic C/C++ mock framework.
    Copyright (C) <2009>  <Darwin Yuan: darwin.yuan@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
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


