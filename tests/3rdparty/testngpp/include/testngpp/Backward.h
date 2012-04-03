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

#ifndef __TESTNGPP_BACKWARD_H
#define __TESTNGPP_BACKWARD_H

#include <testngpp/testngpp.h>
#include <testngpp/Asserter.h>

TESTNGPP_NS_START

#define TS_ASSERT(expr)                        ASSERT_TRUE(expr)
#define TS_ASSERT_EQUALS(expected, actual)     ASSERT_EQ(expected, actual)
#define TS_ASSERT_DIFFERS(expected, actual)    ASSERT_NE(expected, actual)
#define TS_ASSERT_NOT_EQUALS(expected, actual) ASSERT_NE(expected, actual)
#define TS_ASSERT_THROWS(expr, except)         ASSERT_THROWS(expr, except)
#define TS_ASSERT_THROWS_ANYTHING(expr)        ASSERT_THROWS_ANYTHING(expr)
#define TS_ASSERT_THROWS_NOTHING(expr)         ASSERT_THROWS_NOTHING(expr)
#define TS_ASSERT_THROWS_EQUALS(expr, except, expected, value) \
        ASSERT_THROWS_EQ(expr, except, expected, value)
#define TS_FAIL(msg)                           FAIL(msg)
#define TS_WARN(msg)                           WARN(msg)
#define TS_TRACE(msg)                          INFO(msg)

TESTNGPP_NS_END

#endif
