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

#include <mockcpp/ChainableMockMethodNameKey.h>

using namespace mockcpp;

class TestChainableMockMethodNameKey: public TESTCPP_NS::TestFixture
{
   ChainableMockMethodNameKey* key;

   struct ChainableMockMethodNameKeyStub
    : public ChainableMockMethodKey
   {
      ChainableMockMethodNameKeyStub(const std::string& name)
         : methodName(name)
      {}

      bool equals(const ChainableMockMethodKey * const rhs) const
      { return true; }

      std::string& getMethodName() const
      {
          return const_cast<std::string&>(methodName);
      }

   private:
      std::string methodName;
   };

private:

   TESTCPP_RCP checkpoint;

public:

	void setUp()
   {
      checkpoint = TESTCPP_SET_RESOURCE_CHECK_POINT();

      key = new ChainableMockMethodNameKey("method"); 
   }

	void tearDown()
   {
      delete key;
      key = 0;

      TESTCPP_VERIFY_RESOURCE_CHECK_POINT(checkpoint);
   }

   // @test
	void ShouldBeAChainableMockMethodKeyType()
	{
      TS_ASSERT(dynamic_cast<ChainableMockMethodNameKey*>(key) != 0);
   }

   // @test
   void ShouldBeEqualToItself()
   {
      TS_ASSERT(key->equals(key));
   }
   
   // @test
   void ShouldNotEqualToNullPointer()
   {
      TS_ASSERT(!key->equals(0));
   }

   // @test
   void ShouldNotEqualToOtherTypesOfKeys()
   {
      ChainableMockMethodKey* rhs = \
          new ChainableMockMethodNameKeyStub("method");

      __DO__

      TS_ASSERT(!key->equals(rhs));

      __CLEANUP__

      delete rhs;

      __DONE__
   }

   // @test
   void ShouldEqualToSameTypeOfKeysWithSameName()
   {
      ChainableMockMethodKey* rhs = \
          new ChainableMockMethodNameKey("method");

      __DO__

      TS_ASSERT(key->equals(rhs));

      __CLEANUP__

      delete rhs;

      __DONE__
   }

   // @test
   void ShouldNotEqualToSameTypeOfKeysWithDifferentName()
   {
      ChainableMockMethodKey* rhs = \
          new ChainableMockMethodNameKey("method1");

      __DO__

      TS_ASSERT(!key->equals(rhs));

      __CLEANUP__

      delete rhs;

      __DONE__
   }
};

