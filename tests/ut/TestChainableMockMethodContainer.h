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

#include <testcpp/testcpp.hpp>


#include <mockcpp/ChainableMockMethodContainer.h>
#include <mockcpp/ChainableMockMethodCore.h>
#include <mockcpp/InvocationMockBuilderGetter.h>
#include <mockcpp/ChainableMockMethodNameKey.h>
#include <mockcpp/Exception.h>
#include <mockcpp/ChainingMockHelper.h>

USING_MOCKCPP_NS

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

    MOCKCPP_NS::ChainableMockMethodNameKey* key;
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
      MOCKCPP_NS::ChainableMockMethodContainer container;
      container.addMethod(key, method);
      TS_ASSERT_EQUALS(method, container.getMethod(key));
	}

   // @test
   void ShouldReturnNullIfMethodWithTheSpecifiedKeyWasNotAddedToContainer()
   {
      MOCKCPP_NS::ChainableMockMethodContainer container;

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
      MOCKCPP_NS::ChainableMockMethodContainer container;
      container.addMethod(key, method);

      TS_ASSERT_THROWS(container.addMethod(key, method), MOCKCPP_NS::Exception);
   }

   // @test
   void YouCannotGetTheMethodAnyLongerAfterTheContainerIsReset()
   {
      MOCKCPP_NS::ChainableMockMethodContainer container;
      container.addMethod(key, method);
      container.reset();
      TS_ASSERT(0 == container.getMethod(key));
   }

   // @test
   void ShouldBeAbleToVerifyEveryMethodInTheContainer()
   {
      InvocationMockBuilderGetter builderGetter(method, method);

      builderGetter.expects(once());

      MOCKCPP_NS::ChainableMockMethodContainer container;
      container.addMethod(key, method);

      TS_ASSERT_THROWS(container.verify(), MOCKCPP_NS::Exception);
   }
  
   // @test
   void ShouldBeAbleToGetInvocationMockerById()
   {
      InvocationMockBuilderGetter builderGetter(method, method);

      builderGetter.expects(once()).id("1");

      MOCKCPP_NS::ChainableMockMethodContainer container;
      container.addMethod(key, method);

      TS_ASSERT(container.findInvocationMocker("1") != 0);
   }
   
   // @test
   void testShouldReturnNullIfAInvocationMockerWithSpecifiedIdWasNeverBuilt()
   {
      InvocationMockBuilderGetter builderGetter(method, method);

      builderGetter.expects(once()).id("1");

      MOCKCPP_NS::ChainableMockMethodContainer container;
      container.addMethod(key, method);

      TS_ASSERT(container.findInvocationMocker("0") == 0);
   }
};

