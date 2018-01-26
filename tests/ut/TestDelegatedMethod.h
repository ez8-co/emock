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

#include <emock/DelegatedMethod.h>

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
      bool isConst = EMOCK_NS::DelegatedMethod<0,0, EMOCK_NS::ArgumentsList<int> >::IsConst;
      TS_ASSERT(!isConst);
      unsigned int numberOfParameters = EMOCK_NS::DelegatedMethod<0,0, EMOCK_NS::ArgumentsList<int> >::NumberOfParameters;
      TS_ASSERT_EQUALS(0, numberOfParameters);

      /////////////////////////////////////////////////////////////////////////////////////////
      isConst = EMOCK_NS::DelegatedMethod<0,0, EMOCK_NS::ArgumentsListConst<int> >::IsConst;
      TS_ASSERT(isConst);
      numberOfParameters = EMOCK_NS::DelegatedMethod<0,0, EMOCK_NS::ArgumentsListConst<int> >::NumberOfParameters;
      TS_ASSERT_EQUALS(0, numberOfParameters);

      /////////////////////////////////////////////////////////////////////////////////////////
      isConst = EMOCK_NS::DelegatedMethod<0,0, EMOCK_NS::ArgumentsList<int, float> >::IsConst;
      TS_ASSERT(!isConst);
      numberOfParameters = EMOCK_NS::DelegatedMethod<0,0, EMOCK_NS::ArgumentsList<int, float> >::NumberOfParameters;
      TS_ASSERT_EQUALS(1, numberOfParameters);

      /////////////////////////////////////////////////////////////////////////////////////////
      isConst = EMOCK_NS::DelegatedMethod<0,0, EMOCK_NS::ArgumentsListConst<int, float> >::IsConst;
      TS_ASSERT(isConst);
      numberOfParameters = EMOCK_NS::DelegatedMethod<0,0, EMOCK_NS::ArgumentsListConst<int, float> >::NumberOfParameters;
      TS_ASSERT_EQUALS(1, numberOfParameters);
	}

};

