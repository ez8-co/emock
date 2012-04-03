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

#include <mockcpp/InvocationMockerNamespace.h>
#include <mockcpp/InvocationMocker.h>
#include <mockcpp/Method.h>
#include <mockcpp/AfterMatcher.h>
#include <mockcpp/PendingMatcher.h>

MOCKCPP_NS_START

//////////////////////////////////////////////////////////////////////
template <class Builder>
AfterMatchBuilder<Builder>&
AfterMatchBuilder<Builder>::after(const InvocationMockerNamespace& ns, const std::string& name)
{
    return after(&const_cast<InvocationMockerNamespace&>(ns), name);
}

//////////////////////////////////////////////////////////////////////
template <class Builder>
AfterMatchBuilder<Builder>&
AfterMatchBuilder<Builder>::after(InvocationMockerNamespace* ns, const std::string& id)
{
    getMocker()->addMatcher(
			new PendingMatcher(
				new AfterMatcher(),
				  ns, id, getMocker())); 
    return *this;
}

//////////////////////////////////////////////////////////////////////
template <class Builder>
AfterMatchBuilder<Builder>&
AfterMatchBuilder<Builder>::after(const std::string& name)
{
    return after(getMocker()->getMethod()->getNamespace(), name);
}

//////////////////////////////////////////////////////////////////////

MOCKCPP_NS_END


