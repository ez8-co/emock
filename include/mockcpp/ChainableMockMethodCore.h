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

#ifndef __MOCKCPP_CHAINABLE_MOCK_METHOD_CORE_H
#define __MOCKCPP_CHAINABLE_MOCK_METHOD_CORE_H

#include <mockcpp/mockcpp.h>

#include <mockcpp/Method.h>
#include <mockcpp/InvocationMockerContainer.h>

#include <string>

MOCKCPP_NS_START

struct Stub;
struct ChainableMockMethodCoreImpl;
struct SelfDescribe;
struct InvokedRecorder;
struct InvocationMockerNamespace;

struct ChainableMockMethodCore
      : public Method,
		  public InvocationMockerContainer
{
public:

    ChainableMockMethodCore(const std::string& name, 
                            InvocationMockerNamespace* ns);
    ~ChainableMockMethodCore();

    // Method
    const Any& 
        invoke( const std::string& nameOfCaller
              , const RefAny& p1 
              , const RefAny& p2
              , const RefAny& p3
              , const RefAny& p4
              , const RefAny& p5
              , const RefAny& p6
              , const RefAny& p7
              , const RefAny& p8
              , const RefAny& p9
              , const RefAny& p10
              , const RefAny& p11
              , const RefAny& p12
              , SelfDescribe* &resultProvider);

    std::string& getName(void) const;

    InvocationMockerNamespace* getNamespace() const;

public:

    // InvocationMockContainer
    InvocationMocker* getInvocationMocker(const std::string& id);
    void addInvocationMocker(InvocationMocker* mocker);
    void addDefaultInvocationMocker(InvocationMocker* mocker);

public:
    // Others
    void reset();
    void verify();

private:

    ChainableMockMethodCoreImpl* This;
};

MOCKCPP_NS_END

#endif

