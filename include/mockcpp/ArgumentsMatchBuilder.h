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

#ifndef __MOCKCPP_ARGUMENTS_MATCH_BUILDER_H
#define __MOCKCPP_ARGUMENTS_MATCH_BUILDER_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/IsAnythingHelper.h>
#include <mockcpp/DummyBuilder.h>

MOCKCPP_NS_START

struct InvocationMocker;
struct Constraint;

template <typename Builder = DummyBuilder >
struct ArgumentsMatchBuilder : public Builder
{

    Builder& with( const Any& c01 = any()
                 , const Any& c02 = any()
                 , const Any& c03 = any()
                 , const Any& c04 = any()
                 , const Any& c05 = any()
                 , const Any& c06 = any()
                 , const Any& c07 = any()
                 , const Any& c08 = any()
                 , const Any& c09 = any()
                 , const Any& c10 = any()
                 , const Any& c11 = any()
                 , const Any& c12 = any()
    );
#if 0
    Builder& with( Constraint* c01 = any()
                 , Constraint* c02 = any()
                 , Constraint* c03 = any()
                 , Constraint* c04 = any()
                 , Constraint* c05 = any()
                 , Constraint* c06 = any()
                 , Constraint* c07 = any()
                 , Constraint* c08 = any()
                 , Constraint* c09 = any()
                 , Constraint* c10 = any()
                 , Constraint* c11 = any()
                 , Constraint* c12 = any()
    );
#endif

    virtual ~ArgumentsMatchBuilder() {}

private:

    virtual InvocationMocker* getMocker() const = 0;

};

MOCKCPP_NS_END

#include <mockcpp/ArgumentsMatchBuilder.tcc>

#endif

