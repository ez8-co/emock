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

#ifndef __CPPTEST_WRITTABLE_CHANNEL_H
#define __CPPTEST_WRITTABLE_CHANNEL_H

#include <string>

#include <testngpp/testngpp.h>

#include <testngpp/internal/Error.h>

TESTNGPP_NS_START

struct WrittableChannel
{
   virtual void writeByte(const unsigned char byte) TESTNGPP_THROW (Error) = 0;
   virtual void writeInt(const unsigned int value) TESTNGPP_THROW (Error) = 0;
   virtual void writeString(const std::string& str) TESTNGPP_THROW (Error) = 0;

   virtual void close() = 0;

   virtual ~WrittableChannel() {}
};

TESTNGPP_NS_END

#endif

