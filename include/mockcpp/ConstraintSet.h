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

#ifndef __MOCKCPP_CONSTRAINT_SET_H
#define __MOCKCPP_CONSTRAINT_SET_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/StatelessMatcher.h>
#include <mockcpp/IsAnythingHelper.h>

MOCKCPP_NS_START

struct Invocation;
struct Constraint;
struct ConstraintSetImpl;

struct ConstraintSet: public StatelessMatcher
{
    ConstraintSet( Constraint* p01 = any()
                 , Constraint* p02 = any()
                 , Constraint* p03 = any()
                 , Constraint* p04 = any()
                 , Constraint* p05 = any()
                 , Constraint* p06 = any()
                 , Constraint* p07 = any()
                 , Constraint* p08 = any()
                 , Constraint* p09 = any()
                 , Constraint* p10 = any()
                 , Constraint* p11 = any()
                 , Constraint* p12 = any()
    );

    ~ConstraintSet();

    virtual bool matches(const Invocation& inv) const;

    virtual std::string toString() const;

    virtual void verify(void);

private:

    ConstraintSetImpl* This;
};

MOCKCPP_NS_END

#endif

