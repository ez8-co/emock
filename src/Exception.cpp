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


