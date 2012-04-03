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

#ifndef __MOCKCPP_TYPELESS_CONSTRAINT_ADAPTER_H
#define __MOCKCPP_TYPELESS_CONSTRAINT_ADAPTER_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/Constraint.h>

MOCKCPP_NS_START

struct RefAny;
struct TypelessConstraint;
struct TypelessConstraintAdapterImpl;

struct TypelessConstraintAdapter : public Constraint
{
    TypelessConstraintAdapter(TypelessConstraint* tc);
    ~TypelessConstraintAdapter();

    virtual bool eval(const RefAny& p) const;
    virtual std::string toString() const;
    
    TypelessConstraint* getAdaptedConstraint() const;

private:
    TypelessConstraintAdapterImpl* This;
};

MOCKCPP_NS_END

#endif

