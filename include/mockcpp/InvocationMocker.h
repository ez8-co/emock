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

#ifndef __MOCKCPP_INVOCATION_MOCKER_H
#define __MOCKCPP_INVOCATION_MOCKER_H

#include <mockcpp/mockcpp.h>

#include <mockcpp/SelfDescribe.h>

MOCKCPP_NS_START

struct Method;
struct Matcher;
struct Stub;
struct InvocationMockerImpl;
struct Invocation;
struct InvocationId;
struct Any;

struct InvocationMocker : public SelfDescribe
{
    InvocationMocker(Method* core);
    ~InvocationMocker();

    Method* getMethod() const;
    void addStub(Stub* stub);
    void addMatcher(Matcher* matcher);
    bool hasBeenInvoked(void) const ;

    void setId(InvocationId* id);
    const InvocationId* const getId(void) const;

    bool matches(const Invocation& inv) const;
    Any& invoke(const Invocation& inv);

    void verify();

    std::string toString() const;

private:
    InvocationMockerImpl* This;
};

MOCKCPP_NS_END

#endif

