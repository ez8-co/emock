/**
    TestNG++ is a practical, easy-to-use C/C++ xUnit framework.
    Copyright (C) <2009>  <Arthur Yuan: arthur.ii.yuan@gmail.com>

    TestNG++ is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    TestNG++ is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with TestNG++.  If not, see <http://www.gnu.org/licenses/>.
**/

#ifndef __CPPTEST_READABLE_CHANNEL_H
#define __CPPTEST_READABLE_CHANNEL_H

#include <string>

#include <testngpp/testngpp.h>

#include <testngpp/internal/Error.h>
#include <testngpp/runner/EOFError.h>

TESTNGPP_NS_START

struct ReadableChannel
{
   virtual unsigned char readByte() TESTNGPP_THROW (Error, EOFError) = 0;
   virtual int readInt() TESTNGPP_THROW (Error, EOFError) = 0;
   virtual std::string readString() TESTNGPP_THROW (Error, EOFError) = 0;

   virtual void close() = 0;

   virtual ~ReadableChannel() {}
};

TESTNGPP_NS_END

#endif

