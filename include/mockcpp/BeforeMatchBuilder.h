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

#ifndef __MOCKCPP_BEFORE_MATCH_BUILDER_H
#define __MOCKCPP_BEFORE_MATCH_BUILDER_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/DummyBuilder.h>

MOCKCPP_NS_START

struct InvocationMockerNamespace;
struct InvocationMocker;

template < typename Builder = DummyBuilder >
struct BeforeMatchBuilder : public Builder
{
    BeforeMatchBuilder&
	 before(const InvocationMockerNamespace& ns, const std::string& name);

    BeforeMatchBuilder&
	 before(InvocationMockerNamespace* ns, const std::string& name);

    BeforeMatchBuilder&
	 before(const std::string& name);

    virtual ~BeforeMatchBuilder() {}

private:

    void
    setupOrderingBeforeMatchers(InvocationMocker* mocker);

private:

    virtual InvocationMocker* getMocker() const = 0;
};

MOCKCPP_NS_END

#include <mockcpp/BeforeMatchBuilder.tcc>

#endif

