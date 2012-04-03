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

#include <mockcpp/TypelessStubAdapter.h>
#include <mockcpp/TypelessStub.h>

MOCKCPP_NS_START

////////////////////////////////////////////////////////
TypelessStubAdapter::TypelessStubAdapter(TypelessStub* ts)
		: stub(ts)
{}

////////////////////////////////////////////////////////
TypelessStubAdapter::~TypelessStubAdapter()
{
	delete stub;
}

bool TypelessStubAdapter::isCompleted() const
{
   return stub->isCompleted();
}
////////////////////////////////////////////////////////
Any& TypelessStubAdapter::invoke(const Invocation& inv)
{
	return stub->invoke();
}

////////////////////////////////////////////////////////
std::string TypelessStubAdapter::toString() const
{
   return stub->toString();
}

////////////////////////////////////////////////////////

MOCKCPP_NS_END


