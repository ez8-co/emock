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

#ifndef __TESTNGPP_H
#define __TESTNGPP_H

#if !TESTNGPP_NO_NAMESPACE
# define TESTNGPP_NS testngpp
# define TESTNGPP_NS_START namespace TESTNGPP_NS {
# define TESTNGPP_NS_END }
# define USING_TESTNGPP_NS using namespace TESTNGPP_NS;
#else
# define TESTNGPP_NS 
# define TESTNGPP_NS_START 
# define TESTNGPP_NS_END 
# define USING_TESTNGPP_NS 
#endif

#ifdef _MSC_VER
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT 
#endif

#ifdef _MSC_VER
#define TESTNGPP_THROW(...) 
#else
#define TESTNGPP_THROW(...) throw(__VA_ARGS__)
#endif

#endif
