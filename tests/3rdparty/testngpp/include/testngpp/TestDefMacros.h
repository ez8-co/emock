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

#ifndef __TESTNGPP_TEST_DEF_MACROS_H
#define __TESTNGPP_TEST_DEF_MACROS_H

#include <testngpp/testngpp.h>
#include <testngpp/TestModule.h>

#define __TESTNGPP_LINENAME_CAT( name, line ) name##line
#define __LINENAME( name, line ) __TESTNGPP_LINENAME_CAT( name, line )
#define __TESTNGPP_LINENAME( name ) __LINENAME( name, __LINE__ )

#define TEST(name, ...)            void __TESTNGPP_LINENAME(test_) (void)
#define PTEST(paralist, name, ...) void __TESTNGPP_LINENAME(test_) paralist
#define FIXTURE(cut, ...) struct Test##cut: public TESTNGPP_NS::TestFixture

#define SETUP() void setUp()
#define TEARDOWN() void tearDown()

#define MODULE(module, type, ...) struct Module##module : public TESTNGPP_NS::TestModule<type>
#define IMPORT(module, instance, tests) Module##module module##instance

#endif

