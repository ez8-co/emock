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

#include <mockcpp/Exception.h>
#include <mockcpp/MethodInfoReader.h>

class TestMethodInfoReader : public TESTCPP_NS::TestFixture
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
public:
	void setUp() { }
	void tearDown() { }

	/////////////////////////////////////////////////////////

   template <typename Method>
   int getIndexOfMethod(Method m)
   {
		return MOCKCPP_NS::getIndexOfMethod<Interface, Method>(m);
   }

	void testShouldBeAbleToCalcVptrIndex()
	{
      TS_ASSERT(getIndexOfMethod(&Interface::base00) >= 0);
      TS_ASSERT(getIndexOfMethod(&Interface::base01) >= 0);
      TS_ASSERT(getIndexOfMethod(&Interface::base10) >= 0);
      TS_ASSERT(getIndexOfMethod(&Interface::base11) >= 0);
      TS_ASSERT(getIndexOfMethod(&Interface::a) >= 0);
      TS_ASSERT(getIndexOfMethod(&Interface::b) >= 0);

      TS_ASSERT(getIndexOfMethod(&Interface::base00) < 10);
      TS_ASSERT(getIndexOfMethod(&Interface::base01) < 10);
      TS_ASSERT(getIndexOfMethod(&Interface::base10) < 10);
      TS_ASSERT(getIndexOfMethod(&Interface::base11) < 10);
      TS_ASSERT(getIndexOfMethod(&Interface::a) < 10);
      TS_ASSERT(getIndexOfMethod(&Interface::b) < 10);

      TS_ASSERT(getIndexOfMethod(&Interface::base00) != getIndexOfMethod(&Interface::base01));
      TS_ASSERT(getIndexOfMethod(&Interface::base10) != getIndexOfMethod(&Interface::base11));

      TS_ASSERT((getIndexOfMethod(&Interface::base00) != getIndexOfMethod(&Interface::a)) ||
                (getIndexOfMethod(&Interface::base10) != getIndexOfMethod(&Interface::a)));

      TS_ASSERT((getIndexOfMethod(&Interface::base01) != getIndexOfMethod(&Interface::a)) ||
                (getIndexOfMethod(&Interface::base11) != getIndexOfMethod(&Interface::a)));
	}

   void testShouldBeAbleToCalcVptrByBaseClass()
   {
      TS_ASSERT(getIndexOfMethod(&Base0::base00) >= 0);
      TS_ASSERT(getIndexOfMethod(&Base0::base01) >= 0);

      TS_ASSERT(getIndexOfMethod(&Base0::base00) < 10);
      TS_ASSERT(getIndexOfMethod(&Base0::base01) < 10);

      TS_ASSERT(getIndexOfMethod(&Base1::base10) >= 0);
      TS_ASSERT(getIndexOfMethod(&Base1::base11) >= 0);

      TS_ASSERT(getIndexOfMethod(&Base1::base10) < 10);
      TS_ASSERT(getIndexOfMethod(&Base1::base11) < 10);
   }

   template <typename Method>
   int getDeltaOfMethod(Method m)
   {
		return MOCKCPP_NS::getDeltaOfMethod<Interface, Method>(m);
   }

	void testShouldBeAbleToGetVtblIndex()
   {
      TS_ASSERT(getDeltaOfMethod(&Interface::base00) == 0 || \
                getDeltaOfMethod(&Interface::base00) == 1);

      TS_ASSERT(getDeltaOfMethod(&Interface::base10) == 0 || \
                getDeltaOfMethod(&Interface::base10) == 1);

      TS_ASSERT(getDeltaOfMethod(&Interface::a) == 0 || \
                getDeltaOfMethod(&Interface::a) == 1);
   }

	void testShouldBeEqualIf2MethodsDefinedInOneInterface()
   {
      TS_ASSERT(getDeltaOfMethod(&Interface::base00) == getDeltaOfMethod(&Interface::base01));
      TS_ASSERT(getDeltaOfMethod(&Interface::base10) == getDeltaOfMethod(&Interface::base11));
   }

	void testShouldNotBeEqualIf2MethodsDefinedInDifferentBaseInterface()
   {
      TS_ASSERT(getDeltaOfMethod(&Interface::base00) != getDeltaOfMethod(&Interface::base10));
   }

   void testShouldThrowAnExceptionIfTryToGetVtblIndexOfANonVirtualMethod()
   {
      TS_ASSERT_THROWS(getIndexOfMethod(&Interface::c), MOCKCPP_NS::Exception);
   }

   void testShouldThrowAnExceptionIfTryToGetVptrIndexOfANonVirtualMethod()
   {
      TS_ASSERT_THROWS(getDeltaOfMethod(&Interface::c), MOCKCPP_NS::Exception);
   }

   void testShouldThrowAnExceptionIfTryToGetAddressOfAVirtualMethod()
   {
      TS_ASSERT_THROWS(MOCKCPP_NS::getAddrOfMethod(&Interface::base00), MOCKCPP_NS::Exception);
   }
};

