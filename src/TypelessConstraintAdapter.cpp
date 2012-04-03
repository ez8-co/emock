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

#include <mockcpp/TypelessConstraintAdapter.h>
#include <mockcpp/TypelessConstraint.h>

MOCKCPP_NS_START

//////////////////////////////////////////////////////////////////////////
struct TypelessConstraintAdapterImpl
{
   TypelessConstraint* typelessConstraint;

   TypelessConstraintAdapterImpl(TypelessConstraint* c)
		: typelessConstraint(c)
   {}

   ~TypelessConstraintAdapterImpl()
	{
		delete typelessConstraint;
	}
};

//////////////////////////////////////////////////////////////////////////
TypelessConstraintAdapter::TypelessConstraintAdapter(TypelessConstraint* tc)
	: This(new TypelessConstraintAdapterImpl(tc))
{
}

//////////////////////////////////////////////////////////////////////////
TypelessConstraintAdapter::~TypelessConstraintAdapter()
{
    delete This;
}

//////////////////////////////////////////////////////////////////////////
bool
TypelessConstraintAdapter::eval(const RefAny& p) const
{
    return This->typelessConstraint->eval();
}

//////////////////////////////////////////////////////////////////////////
TypelessConstraint*
TypelessConstraintAdapter::getAdaptedConstraint() const
{
	return This->typelessConstraint;
}
//////////////////////////////////////////////////////////////////////////
std::string TypelessConstraintAdapter::toString() const
{
	return This->typelessConstraint->toString();
}

MOCKCPP_NS_END

