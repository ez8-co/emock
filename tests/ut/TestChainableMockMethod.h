/***
   emock is a cross-platform easy-to-use C++ Mock Framework based on mockcpp.
   Copyright [2017] [ez8.co] [orca <orca.zhang@yahoo.com>]

   This library is released under the Apache License, Version 2.0.
   Please see LICENSE file or visit https://github.com/ez8-co/emock for details.

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
#include <string>
#include <sstream>

#include <testcpp/testcpp.hpp>

#include <emock/Invokable.h>

#include <emock/ChainableMockMethod.h>
#include <emock/ChainingMockHelper.h>

USING_EMOCK_NS
USING_TESTCPP_NS

class TestChainableMockMethod: public TESTCPP_NS::TestFixture
{
   struct InvokableStub : public Invokable
   {

    InvokableStub(const std::string& returned)
      : stub(returnValue(returned))
    {}

    ~InvokableStub()
    {
       delete stub;
    }

    const Any& invoke( const std::string& nameOfCaller
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
        Invocation inv(nameOfCaller, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12);
        return stub->invoke(inv); 
     }

     Stub* stub;
   };

private:

   TESTCPP_RCP checkpoint;
   Invokable* invokable;

public:

   void setUp()
   {
      checkpoint = TESTCPP_SET_RESOURCE_CHECK_POINT();
      invokable = new InvokableStub("abcdefg");
   }

   void tearDown()
   {
      delete invokable;
      TESTCPP_VERIFY_RESOURCE_CHECK_POINT(checkpoint);
   }

   // @test
   void shouldBeAbleToReturnAReferenceType()
   {
      ChainableMockMethod<const std::string&> method(invokable);
      std::string str = method(__FUNCTION__);
      TS_ASSERT_EQUALS(std::string("abcdefg"), str);
   }

   // @test
   void shouldBeAbleToReturnAReferenceTypeDirectly()
   {
      ChainableMockMethod<const std::string&> method(invokable);
      TS_ASSERT_EQUALS(std::string("abcdefg"), method(__FUNCTION__));
   }
};
