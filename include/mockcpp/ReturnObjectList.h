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

#ifndef __MOCKCPP_RETURN_OBJECT_LIST_H
#define __MOCKCPP_RETURN_OBJECT_LIST_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/TypelessStub.h>

MOCKCPP_NS_START

struct ReturnObjectListImpl;

struct ReturnObjectList : public TypelessStub
{
public:

    ReturnObjectList( const Any& o01 = Any()
                    , const Any& o02 = Any()
                    , const Any& o03 = Any()
                    , const Any& o04 = Any()
                    , const Any& o05 = Any()
                    , const Any& o06 = Any()
                    , const Any& o07 = Any()
                    , const Any& o08 = Any()
                    , const Any& o09 = Any()
                    , const Any& o10 = Any()
                    , const Any& o11 = Any()
                    , const Any& o12 = Any()
                    );

    ~ReturnObjectList();

    bool isCompleted(void) const;
    Any& invoke(void);

    std::string toString(void) const;

    const std::type_info& type() const;

private:

    ReturnObjectListImpl* This;
};

MOCKCPP_NS_END

#endif

