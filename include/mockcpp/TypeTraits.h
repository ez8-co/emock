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


#ifndef __MOCKCPP_TYPE_TRAITS_H
#define __MOCKCPP_TYPE_TRAITS_H

#include <mockcpp/mockcpp.h>

MOCKCPP_NS_START

/*
 * For non-reference type
 */
template <typename T>
struct TypeTraits
{
    typedef T          Raw;
    typedef T&         RefRaw;

    typedef T          Type;
    typedef T&         Ref;
};

/*
 * For non-reference type
 */
template <typename T>
struct TypeTraits<const T>
{
    typedef T          Raw;
    typedef T&         RefRaw;

    typedef T          Type;
    typedef const T&   Ref;
};

/*
 * For non-reference type
 */
template <typename T>
struct TypeTraits<const T*>
{
    typedef T*         Raw;
    typedef T*&        RefRaw;

    typedef const T*   Type;
    typedef const T*&  Ref;
};

/*
 * For reference type
 */
template <typename T>
struct TypeTraits<T&>
{
    typedef T         Raw;
    typedef T&        RefRawx;

    typedef T         Type;
    typedef T&        Ref;
};

/*
 * For reference type
 */
template <typename T>
struct TypeTraits<const T&>
{
    typedef T         Raw;
    typedef T&        RefRaw;

    typedef T         Type;
    typedef const T&  Ref;
};

/*
 * For non-reference type
 */
template <>
struct TypeTraits<void>
{
    typedef void      Raw;
    typedef void      RefRaw;

    typedef void      Type;
    typedef void      Ref;
};

MOCKCPP_NS_END

#endif // __MOCKCPP_TYPE_TRAITS_H

