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

#include <testcpp/testcpp.hpp>


#include <emock/ChainableMockMethodContainer.h>
#include <emock/ChainableMockMethodCore.h>
#include <emock/InvocationMockBuilderGetter.h>
#include <emock/ChainableMockMethodNameKey.h>
#include <emock/Exception.h>
#include <emock/ChainingMockHelper.h>

USING_EMOCK_NS

class TestChainableMockMethodContainer : public TESTCPP_NS::TestFixture
{
   struct InvocationMockerNamespaceStub : public InvocationMockerNamespace
   {
      InvocationMockerNamespaceStub()
			: name("InvocationMockerNamespaceStub")
      {}

      InvocationMocker* getInvocationMocker(const std::string& id)  const
      {
         return 0;
      }

      std::string& getName(void) const
      {
         return const_cast<std::string&>(name);
      } 

      std::string name;
   };

private:

    EMOCK_NS::ChainableMockMethodNameKey* key;
    InvocationMockerNamespaceStub ns;
    ChainableMockMethodCore* method;

private:

   TESTCPP_RCP checkpoint;

public:

	void setUp()
   {
      checkpoint = TESTCPP_SET_RESOURCE_CHECK_POINT();

      key = new ChainableMockMethodNameKey("method");
		method = new ChainableMockMethodCore("method", &ns);

   }

	void tearDown()
   {
      TESTCPP_VERIFY_RESOURCE_CHECK_POINT(checkpoint);
   }

	/////////////////////////////////////////////////////////

   // @test
	void shouldBeAbleToAddAMethod()
	{
      EMOCK_NS::ChainableMockMethodContainer container;
      container.addMethod(key, method);
      TS_ASSERT_EQUALS(method, container.getMethod(key));
	}

   // @test
   void ShouldReturnNullIfMethodWithTheSpecifiedKeyWasNotAddedToContainer()
   {
      EMOCK_NS::ChainableMockMethodContainer container;

      __DO__

      TS_ASSERT(0 == container.getMethod(key));

      __CLEANUP__

      delete key;
	  delete method;

      __DONE__
   }

   // @test
   void ShouldThrowExceptionIfAMethodWithTheSameKeyHasBeedAdded()
   {
      EMOCK_NS::ChainableMockMethodContainer container;
      container.addMethod(key, method);

      TS_ASSERT_THROWS(container.addMethod(key, method), EMOCK_NS::Exception);
   }

   // @test
   void YouCannotGetTheMethodAnyLongerAfterTheContainerIsReset()
   {
      EMOCK_NS::ChainableMockMethodContainer container;
      container.addMethod(key, method);
      container.reset();
      TS_ASSERT(0 == container.getMethod(key));
   }

   // @test
   void ShouldBeAbleToVerifyEveryMethodInTheContainer()
   {
      InvocationMockBuilderGetter builderGetter(method, method);

      builderGetter.expects(once());

      EMOCK_NS::ChainableMockMethodContainer container;
      container.addMethod(key, method);

      TS_ASSERT_THROWS(container.verify(), EMOCK_NS::Exception);
   }
  
   // @test
   void ShouldBeAbleToGetInvocationMockerById()
   {
      InvocationMockBuilderGetter builderGetter(method, method);

      builderGetter.expects(once()).id("1");

      EMOCK_NS::ChainableMockMethodContainer container;
      container.addMethod(key, method);

      TS_ASSERT(container.findInvocationMocker("1") != 0);
   }
   
   // @test
   void testShouldReturnNullIfAInvocationMockerWithSpecifiedIdWasNeverBuilt()
   {
      InvocationMockBuilderGetter builderGetter(method, method);

      builderGetter.expects(once()).id("1");

      EMOCK_NS::ChainableMockMethodContainer container;
      container.addMethod(key, method);

      TS_ASSERT(container.findInvocationMocker("0") == 0);
   }
};

