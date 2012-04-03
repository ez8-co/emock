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

#include <iostream>
#include <mockcpp/MockObject.h>
#include <mockcpp/ChainingMockHelper.h>

USING_MOCKCPP_NS

// @fixture(tags=ft)
class TestMockObject2 : public TESTCPP_NS::TestFixture
{

	struct Base0
   {
      virtual int  base00() = 0;
      virtual bool base01(long) const = 0;
      virtual ~Base0() {}
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
      virtual const std::string& a() {}
      virtual void b(bool) {}

      enum Result
      {
         S_OK,
         S_FAILED
      };

      virtual Result getResult() const = 0;
      virtual unsigned int getResult1() const = 0;
      virtual void setResult(int) = 0;
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

   // returnValue() : int => enum
   void testShouldBeAbleToConvertReturnValueFromIntToEnum()
   {
      MockObject<Interface> mock;
      mock.method(&Interface::getResult).stubs().will(returnValue(1));

      TS_ASSERT_EQUALS(Interface::S_FAILED, mock->getResult());
   }

   TEST(getResult : "unsigned int" => "unsigned int")
   {
      MockObject<Interface> mock;
      mock.method(&Interface::getResult1).stubs().will(returnValue((unsigned int)1));

      TS_ASSERT_EQUALS(1, mock->getResult1());
   }

#if 0
   // returnValue() : enum => unsigned int 
   void testShouldBeAbleToConvertReturnValueFromEnumToInt()
   {
      MockObject<Interface> mock;
      mock.method(&Interface::getResult1)
          .stubs().will(returnValue(Interface::S_FAILED));

      TS_ASSERT_EQUALS(1, mock->getResult1());
   }
#endif

   // eq() : int => enum
   void testShouldBeAbleToConvertConstraintsFromIntToEnum()
   {
      MockObject<Interface> mock;
      mock.method(&Interface::setResult)
         .expects(once()).with(eq(Interface::S_FAILED));

      mock->setResult(1);

      mock.verify();
   }

   // returnValue() : int => long
   void testShouldBeAbleToConvertReturnValue()
   {
      MockObject<Interface> mock;
      mock.method(&Interface::base11).stubs().will(returnValue((long)12));

      TS_ASSERT_EQUALS(12, mock->base11(""));
   }

   // eq() : int => long
   void testShouldBeAbleToConvertConstraints()
   {
      MockObject<Interface> mock;
      mock.method(&Interface::base01)
        .stubs().with(eq((long)10)).will(returnValue(true));

      TS_ASSERT(mock->base01(10));
   }

   // typeid()
   void testShouldBeAbleToGetTypeInfoOfAMockObject()
   {
      MockObject<Interface> mock;
      Interface* pInterface = (Interface*)mock;

      TS_ASSERT(typeid(pInterface) == typeid(Interface*));
   }

   // dynamic_cast
   void testShouldSupportDownCast1()
   {
      #ifndef _MSC_VER
	  //VC does not support   
      MockObject<Interface> mock;
      mock.method(&Interface::base00).stubs().will(returnValue(10));
      Base0* pBase0 = (Base0*)mock;
      TS_ASSERT_EQUALS(10, pBase0->base00());
      Interface* p = dynamic_cast<Interface*>(pBase0);
      TS_ASSERT(p != 0);
      TS_ASSERT_EQUALS(10, p->base00());
	  #endif
   }

   // dynamic_cast to second
   void testShouldSupportDownCast2()
   {
      #ifndef _MSC_VER
	  //VC does not support
      MockObject<Interface> mock;

      mock.method(&Interface::base12).stubs().will(returnValue(10));

      Base1* pBase1 = (Base1*)mock;
      TS_ASSERT_EQUALS(10, pBase1->base12());

      Interface* p = dynamic_cast<Interface*>(pBase1);
      TS_ASSERT(p != 0);
      TS_ASSERT((void*)pBase1 != (void*)p);

      TS_ASSERT_EQUALS(10, p->base12());
	  #endif
   }

   // delete
   void testShouldSupportDeleteAMockObjectWhoMocksASimpleInterface()
   {
      MockObject<Base1> mock;

      Base1* p = mock;

      delete p;
   }

   // delete
   void testShouldSupportDeleteAMockObjectWhoMocksAInterfaceWhichInhritedFromOthers()
   {
      MockObject<Interface> mock;

      Interface* p = mock;

      delete p;
   }

   // delete
   void testShouldSupportDeleteAMockObjectWhoMocksAInterfaceWhichInhritedByOthers()
   {
      MockObject<Interface> mock;

      Base0* p = mock;

      delete p;
   }

   // delete
   void testShouldSupportDeleteAMockObjectWhoMocksAInterfaceWhichInhritedByOthersAsNonFirstParent()
   {
      MockObject<Interface> mock;

      mock.mightBeUsedAs<Base1>();

      Base1* p = mock;

      delete p;
   }

   // willBeDeleted
   void testShouldBeAbleToSpecifyAnObjectShouldBeDeletedLater()
   {
      MockObject<Interface> mock;
      mock.willBeDeleted();
      TS_ASSERT_THROWS(mock.verify(), Exception);
   }

   // willBeDeleted
   void testShouldPassVerifyIfAnObjectIsDeletedAsExpected()
   {
      MockObject<Interface> mock;
      mock.willBeDeleted();

      delete (Interface*)mock;

      TS_ASSERT_THROWS_NOTHING(mock.verify());
   }

   // willKeepAlive
   void testShouldBeAbleToSpecifyAnObjectShouldKeepAlive()
   {
      MockObject<Interface> mock;
      mock.willKeepAlive();
      TS_ASSERT_THROWS(delete (Interface*) mock, Exception);
   }

   // willKeepAlive
   void testShouldPassVerificationIfAnObjectKeepsAliveAsExpected()
   {
      MockObject<Interface> mock;
      mock.willKeepAlive();

      TS_ASSERT_THROWS_NOTHING(mock.verify());
   }

   void testShouldStillBeDeletableAfterAMockObjectIsReset()
   {
      MockObject<Interface> mock;
      delete (Interface*) mock;
      mock.reset();
      TS_ASSERT_THROWS_NOTHING(delete (Interface*)mock);
   }


   struct WrongInterface { virtual void foo() = 0; };

   TEST(Interface Without Virtual Destructor : throw Exception)
   {
      TS_ASSERT_THROWS(MockObject<WrongInterface> mock, Exception);
   }
};

