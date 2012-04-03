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

#ifndef __MOCKCPP_H
#define __MOCKCPP_H


#if !defined(MOCKCPP_NO_NAMESPACE) || (MOCKCPP_NO_NAMESPACE == 0)
# define MOCKCPP_NS mockcpp
# define MOCKCPP_NS_START namespace MOCKCPP_NS {
# define MOCKCPP_NS_END }
# define USING_MOCKCPP_NS using namespace MOCKCPP_NS;
#else
# define MOCKCPP_NS 
# define MOCKCPP_NS_START 
# define MOCKCPP_NS_END 
# define USING_MOCKCPP_NS 
#endif

#ifdef _MSC_VER
# define MOCKCPP_EXPORT __declspec(dllexport)
#else
# define MOCKCPP_EXPORT 
#endif


#if  ( defined (__LP64__) \
    || defined (__64BIT__) \
    || defined (_LP64) \
    || ((defined(__WORDSIZE)) && (__WORDSIZE == 64)) \
	|| defined(WIN64))

#define BUILD_FOR_X64 1
#define BUILD_FOR_X86 0

#else	

#define BUILD_FOR_X64 0
#define BUILD_FOR_X86 1

#endif

template <bool condition>
struct static_assert
{
    typedef int static_assert_failure[condition ? 1 : -1];
};


#endif // __MOCKCPP_H

