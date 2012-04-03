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

#ifndef __TESTNGPP_TESTCPP_HPP__
#define __TESTNGPP_TESTCPP_HPP__

#include <testngpp/testngpp.hpp>

// backward-compatible
#define testcpp     testngpp
#define TESTCPP_NS testcpp
#define USING_TESTCPP_NS using namespace TESTCPP_NS;

#define TESTCPP_RCP int
#define TESTCPP_SET_RESOURCE_CHECK_POINT() (0) 
#define TESTCPP_VERIFY_RESOURCE_CHECK_POINT(rcp) do { }while(0)

#endif

