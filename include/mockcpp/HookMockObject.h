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

#ifndef __MOCKCPP_HOOK_MOCK_OBJECT_H__
#define __MOCKCPP_HOOK_MOCK_OBJECT_H__

#include <mockcpp/mockcpp.h>
#include <mockcpp/ChainableMockObjectBase.h>
#include <mockcpp/InvocationMockBuilderGetter.h>
#include <mockcpp/ChainableMockMethod.h>

MOCKCPP_NS_START

struct ApiHookHolder;
struct HookMockObjectImpl;

struct HookMockObject : public ChainableMockObjectBase
{
    HookMockObject(const std::string& name);
    ~HookMockObject();

    // Building-invocation-mocker interface -- Used in test case
    InvocationMockBuilderGetter method
               ( const std::string& name
               , const void* api
               , ApiHookHolder* holder);

    // Invoking interface --  Used in Functor
    template <typename RT>
    ChainableMockMethod<RT> invoke(const void* api) 
    {
      return ChainableMockMethod<RT>(getInvokable(api)); 
    }

    void reset();

private:

    // It's only for template-method invoke. we have to make it visible.
    Invokable* getInvokable(const void* api);

private:	
    HookMockObjectImpl* This;	
};

MOCKCPP_NS_END

#endif
