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

#include <mockcpp/types/Any.h>
#include <mockcpp/Stub.h>
#include <mockcpp/Asserter.h>
#include <mockcpp/Invocation.h>
#include <mockcpp/InvocationId.h>
#include <mockcpp/DefaultMatcher.h>
#include <mockcpp/StubsMatcher.h>
#include <mockcpp/ExpectsMatcher.h>
#include <mockcpp/InvocationMocker.h>
#include <mockcpp/InvokedTimesMatcher.h>
#include <mockcpp/InvocationMockerSet.h>
#include <mockcpp/InvokedTimesRecorder.h>
#include <mockcpp/InvocationTimesMatcher.h>
#include <mockcpp/ChainableMockMethodCore.h>
#include <mockcpp/SimpleInvocationRecorder.h>

MOCKCPP_NS_START

//////////////////////////////////////////////////////////
struct ChainableMockMethodCoreImpl
{
    std::string methodName;
    /////////////////////////////////////////////////////
    InvocationMockerSet mockers;
    InvocationMockerSet defaultMockers;
    InvocationMockerNamespace* invocationMockerNamespace;

	 /////////////////////////////////////////////////////
    ChainableMockMethodCoreImpl(const std::string& name, InvocationMockerNamespace* ns)
            : methodName(name), invocationMockerNamespace(ns) {}

    ~ChainableMockMethodCoreImpl();
   
    InvocationMocker* getInvocationMocker(const std::string& id) const;
    std::string tellNoMatchedExpectation(const Invocation& inv);
    std::string toString() const;
    const Any& invoke(const Invocation& inv, SelfDescribe* &resultProvider);
    void reset();
    void verify();
};

/////////////////////////////////////////////////////////////
std::string ChainableMockMethodCoreImpl::toString() const
{
    return mockers.toString() + defaultMockers.toString();
}

/////////////////////////////////////////////////////////////
void ChainableMockMethodCoreImpl::verify()
{
    mockers.verify();
}

/////////////////////////////////////////////////////////////
ChainableMockMethodCoreImpl::~ChainableMockMethodCoreImpl()
{
    reset();
}

/////////////////////////////////////////////////////////////
void ChainableMockMethodCoreImpl::reset()
{
    mockers.reset();
    defaultMockers.reset();
}
 
/////////////////////////////////////////////////////////////
InvocationMocker*
ChainableMockMethodCoreImpl::
getInvocationMocker(const std::string& id) const
{
    return mockers.getInvocationMocker(id);
}

/////////////////////////////////////////////////////////////
std::string
ChainableMockMethodCoreImpl::
tellNoMatchedExpectation(const Invocation& inv)
{
    return std::string("\n")
       + "=====================================\n"
       + std::string("Unexpected invocation: the invocation cannot be found in allowed invoking list.") + "\n" 
       + "Invoked: " + methodName + inv.toString() + "\n"
       + "Allowed: \n"
       + this->toString()
       + "=====================================\n";
}

/////////////////////////////////////////////////////////////
const Any&
ChainableMockMethodCoreImpl::invoke(const Invocation& inv
                                   , SelfDescribe* &resultProvider)
{
    const Any& result1 = mockers.invoke(inv, resultProvider);
    if (!result1.empty())
    {
      return result1;
    }

    const Any& result2 = defaultMockers.invoke(inv, resultProvider);
    if (!result2.empty())
    {
      return result2;
    }

	 MOCKCPP_FAIL(tellNoMatchedExpectation(inv));
   
	 return getEmptyAny();
}

//////////////////////////////////////////////////////////
ChainableMockMethodCore::
ChainableMockMethodCore(const std::string& name, InvocationMockerNamespace* ns)
   : This(new ChainableMockMethodCoreImpl(name, ns))
{
}

//////////////////////////////////////////////////////////
ChainableMockMethodCore::~ChainableMockMethodCore()
{
    delete This;
}

//////////////////////////////////////////////////////////
std::string&
ChainableMockMethodCore::getName() const
{
   return This->methodName;
}

//////////////////////////////////////////////////////////
const Any&
ChainableMockMethodCore::invoke
             ( const std::string& nameOfCaller
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
             , SelfDescribe* &resultProvider)
{
    Invocation inv(nameOfCaller,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12);
    return This->invoke(inv, resultProvider);
}

//////////////////////////////////////////////////////////
InvocationMocker*
ChainableMockMethodCore::getInvocationMocker(const std::string& id)
{
    return This->getInvocationMocker(id);
}

//////////////////////////////////////////////////////////
void
ChainableMockMethodCore::addInvocationMocker(InvocationMocker* mocker)
{
    This->mockers.addInvocationMocker(mocker);
}

//////////////////////////////////////////////////////////
void
ChainableMockMethodCore::addDefaultInvocationMocker(InvocationMocker* mocker)
{
    This->defaultMockers.addInvocationMocker(mocker);
}

//////////////////////////////////////////////////////////
InvocationMockerNamespace* ChainableMockMethodCore::getNamespace() const
{
    return This->invocationMockerNamespace;
}

//////////////////////////////////////////////////////////
void ChainableMockMethodCore::reset()
{
    This->reset();
}

//////////////////////////////////////////////////////////
void ChainableMockMethodCore::verify()
{
    This->verify();
}

//////////////////////////////////////////////////////////

MOCKCPP_NS_END

