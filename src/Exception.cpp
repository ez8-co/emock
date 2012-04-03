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

#include <mockcpp/Exception.h>

MOCKCPP_NS_START

#if !defined(MOCKCPP_USING_CPPUNIT)

Exception::Exception (unsigned line, const char* file, const std::string& msg )
	: std::exception()
	, message(msg)
	, srcline(line)
	, srcfile(file)
{
}

//////////////////////////////////////////////////////
Exception::~Exception() throw()
{
}

//////////////////////////////////////////////////////
std::string Exception::getMessage() const
{
    return message;
}

//////////////////////////////////////////////////////
unsigned Exception::getSrcLine() const
{
    return srcline;
}

//////////////////////////////////////////////////////
std::string Exception::getSrcFile() const
{
    return srcfile;
}

//////////////////////////////////////////////////////
const char* Exception::what() const throw()
{
    what_helper = getMessage();
    return what_helper.c_str();
}

#endif

MOCKCPP_NS_END


