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

#include <emock/InterfaceInfo.h>
#include <emock/Exception.h>

USING_EMOCK_NS
USING_TESTCPP_NS

class TestInterfaceInfo: public TESTCPP_NS::TestFixture
{
   struct Base0 { virtual void base0() {}; virtual ~Base0() {} };
   struct Base1 { virtual ~Base1() {} };

   struct Derived0 : public Base0 {};
   struct Derived1 : public Base0 {};

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

   void testShouldBeAbleCalculateNumberOfVptr_SingleInheritance()
   {
      TS_ASSERT_EQUALS(1, getNumberOfVtbls<Derived0>());
   }

   struct Derived2 : public Base0, public Base1 {};

   void testShouldBeAbleCalculateNumberOfVptr_MultiInheritance()
   {
      TS_ASSERT_EQUALS(2, getNumberOfVtbls<Derived2>());
   }

   struct Derived3 : public Derived0, public Derived1 {};
   struct Derived4 : public Derived3 {};

   void testShouldBeAbleCalculateTheNumberOfVptr_MultiInheritance2()
   {
      TS_ASSERT_EQUALS(sizeof(Derived4)/sizeof(void*), getNumberOfVtbls<Derived4>());
   }

   struct Derived5 : public Derived2, public Derived0 {};
   void testShouldBeAbleToCalculateTheNumberOfVptr_DupInheritance()
   {
      TS_ASSERT_EQUALS(sizeof(Derived5)/sizeof(void*), getNumberOfVtbls<Derived5>());
   }
 
   struct Derived6 : virtual public Derived2, virtual public Derived0 {};
   void testShouldBeThrowExcpetion_VirtualInheritance()
   {
      #ifndef _MSC_VER
	  //VC does not support
      TS_ASSERT_THROWS(getNumberOfVtbls<Derived6>(), EMOCK_NS::Exception);
	  #endif
   }
};
