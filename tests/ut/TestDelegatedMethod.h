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

#include <mockcpp/DelegatedMethod.h>

class TestDelegatedMethod: public TESTCPP_NS::TestFixture
{
	struct Base0
   {
      virtual int  base00() = 0;
      virtual bool base01(int) const = 0;
      virtual ~Base0() {}
   };

   struct Base1
   {
      virtual void base10() = 0;
      virtual long base11(bool) const = 0;

      virtual ~Base1() {}
   };

   struct Interface: public Base0, public Base1
   {
      virtual void a() {}
      virtual void b(bool) {}
      void c() {}
   };

private:

   TESTCPP_RCP checkpoint;

public:

   void setUp()
   {
      checkpoint = TESTCPP_SET_RESOURCE_CHECK_POINT();

   }
   void tearDown()
   {
      TESTCPP_VERIFY_RESOURCE_CHECK_POINT(checkpoint);
   }


	/////////////////////////////////////////////////////////

	void testShouldBeAbleToChooseCorrectDelegatedMethod()
	{
      bool isConst = MOCKCPP_NS::DelegatedMethod<0,0, MOCKCPP_NS::ArgumentsList<int> >::IsConst;
      TS_ASSERT(!isConst);
      unsigned int numberOfParameters = MOCKCPP_NS::DelegatedMethod<0,0, MOCKCPP_NS::ArgumentsList<int> >::NumberOfParameters;
      TS_ASSERT_EQUALS(0, numberOfParameters);

      /////////////////////////////////////////////////////////////////////////////////////////
      isConst = MOCKCPP_NS::DelegatedMethod<0,0, MOCKCPP_NS::ArgumentsListConst<int> >::IsConst;
      TS_ASSERT(isConst);
      numberOfParameters = MOCKCPP_NS::DelegatedMethod<0,0, MOCKCPP_NS::ArgumentsListConst<int> >::NumberOfParameters;
      TS_ASSERT_EQUALS(0, numberOfParameters);

      /////////////////////////////////////////////////////////////////////////////////////////
      isConst = MOCKCPP_NS::DelegatedMethod<0,0, MOCKCPP_NS::ArgumentsList<int, float> >::IsConst;
      TS_ASSERT(!isConst);
      numberOfParameters = MOCKCPP_NS::DelegatedMethod<0,0, MOCKCPP_NS::ArgumentsList<int, float> >::NumberOfParameters;
      TS_ASSERT_EQUALS(1, numberOfParameters);

      /////////////////////////////////////////////////////////////////////////////////////////
      isConst = MOCKCPP_NS::DelegatedMethod<0,0, MOCKCPP_NS::ArgumentsListConst<int, float> >::IsConst;
      TS_ASSERT(isConst);
      numberOfParameters = MOCKCPP_NS::DelegatedMethod<0,0, MOCKCPP_NS::ArgumentsListConst<int, float> >::NumberOfParameters;
      TS_ASSERT_EQUALS(1, numberOfParameters);
	}

};

