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

#include <iostream>
#include <emock/ChainingMockHelper.h>
#include <emock/emock.hpp>

USING_EMOCK_NS

// @fixture(tags=ft)
class TestMockObject : public TESTCPP_NS::TestFixture
{

	struct Base0
   {
      virtual int  base00() = 0;
      virtual bool base01(int) const = 0;
      virtual ~Base0() {}
      virtual int base20() {return 0;}
      virtual int base20(int) {return 0;}
      virtual int base20(double) {return 0;}
   };

   struct Base1
   {
      virtual void base10() = 0;
      virtual long base11(const std::string&) const = 0;
      virtual int  base12() const = 0;

      virtual ~Base1() {}
   };

   struct Interface: public Base0, public Base1
   {
	    virtual const std::string& a() { static std::string str; return str; }
      virtual void b(bool) {}
   };

   struct Dervied: public Interface
   {
      virtual int  base00() {return 0;}
      virtual bool base01(int) const {return true;}
      virtual void base10() {}
      virtual long base11(const std::string&) const {return 0;}
      virtual int  base12() const {return 1;}
   };


private:

	TESTCPP_RCP checkpoint;
   std::string str;

public:

	void setUp()
   {
      str = "abcdefg";

		checkpoint = TESTCPP_SET_RESOURCE_CHECK_POINT();
   }

	void tearDown()
   {
      TESTCPP_VERIFY_RESOURCE_CHECK_POINT(checkpoint);
   }
   
   void testShouldBeAbleToSupportMocker()
   {
      Dervied o;
      EMOCK(&Dervied::base00)
           .stubs()
           .will(returnValue(20))
           .then(returnValue(10))
           .then(returnValue(1))
           .then(returnValue(5));

      TS_ASSERT_EQUALS(20, o.base00());
      TS_ASSERT_EQUALS(10, o.base00());
      TS_ASSERT_EQUALS(1, o.base00());
      TS_ASSERT_EQUALS(5, o.base00());
      TS_ASSERT_EQUALS(5, o.base00());
      GlobalMockObject::verify();

      EMOCK((int (Base0::*)())&Base0::base20)
           .stubs()
           .will(returnValue(20));
      TS_ASSERT_EQUALS(20, o.base20());
      GlobalMockObject::verify();

      EMOCK(static_cast<int (Base0::*)(int)>(&Base0::base20))
           .stubs()
           .will(returnValue(10));
      TS_ASSERT_EQUALS(10, o.base20(0));
      GlobalMockObject::verify();

      EMOCK(static_cast<int (Base0::*)(double)>(&Base0::base20))
           .stubs()
           .will(returnValue(5));
      TS_ASSERT_EQUALS(5, o.base20(0.0));
      GlobalMockObject::verify();
   }

};

