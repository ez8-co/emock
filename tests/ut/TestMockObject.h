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
class TestMockObject : public TESTCPP_NS::TestFixture
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
      virtual long base11(const std::string&) const = 0;
      virtual int  base12() const = 0;

      virtual ~Base1() {}
   };

   struct Interface: public Base0, public Base1
   {
      virtual const std::string& a() {}
      virtual void b(bool) {}
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

	/////////////////////////////////////////////////////////

   // will()
   void testShouldBeAbleReturnTheExpectedValue()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base00).stubs().will(returnValue(20));

       TS_ASSERT_EQUALS(20, mock->base00());
       TS_ASSERT_EQUALS(20, mock->base00());
       TS_ASSERT_EQUALS(20, mock->base00());
   }

   // then()
   void testShouldBeAbleToReturnTheExpectedValueAccordingToTheSequenceOfStubs()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base00).stubs().will(returnValue(20)).then(returnValue(10));

       TS_ASSERT_EQUALS(20, mock->base00());
       TS_ASSERT_EQUALS(10, mock->base00());
       TS_ASSERT_EQUALS(10, mock->base00());
   }

   // then()
   void testShouldBeAbleToSupportMultipleThenSpecification()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base00)
           .stubs()
           .will(returnValue(20))
           .then(returnValue(10))
           .then(returnValue(1))
           .then(returnValue(5));

       TS_ASSERT_EQUALS(20, mock->base00());
       TS_ASSERT_EQUALS(10, mock->base00());
       TS_ASSERT_EQUALS(1, mock->base00());
       TS_ASSERT_EQUALS(5, mock->base00());
       TS_ASSERT_EQUALS(5, mock->base00());
   }

   //void testShouldBeAbleReturnValueRepeatedly()
   //void testShouldThrowExceptionAfterRepeatingSpecifiedTimesAndNoSubsequentStubSpecified()
   //void testShouldBeAbleReturnValueIncrementallyWithinAScope()

   // repeat()
   TEST(repeat(num, times)在重复返回num达到指定次数times之后，如果有指定的后续行为，则执行后续行为)

   {
       MockObject<Interface> mock;

       mock.method(&Interface::base00).stubs().will(repeat(20, 2)).then(returnValue(10));

       TS_ASSERT_EQUALS(20, mock->base00());
       TS_ASSERT_EQUALS(20, mock->base00());
       TS_ASSERT_EQUALS(10, mock->base00());
   }

   // repeat()
   TEST(repeat(num, times)在重复返回num达到指定的次数times之后，如果无指定后续行为，再次调用将抛出异常)
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base00).stubs().will(repeat(20, 2));

       TS_ASSERT_EQUALS(20, mock->base00());
       TS_ASSERT_EQUALS(20, mock->base00());
       
       TS_ASSERT_THROWS(mock->base00(), Exception);
   }

   // increase()
   TEST(increase(num, times)在重复返回num+invoke times-1达到指定次数times之后，如果有指定的后续行为，则执行后续行为)
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base00).stubs().will(increase(1, 3)).then(returnValue(10));

       TS_ASSERT_EQUALS(1, mock->base00());
       TS_ASSERT_EQUALS(2, mock->base00());
       TS_ASSERT_EQUALS(3, mock->base00());
       TS_ASSERT_EQUALS(10, mock->base00());
   }

   // increase()
   void testShouldBeAbleReturnValueIncrementallyWithoutEnding()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base00).stubs().will(increase(1)).then(returnValue(10));

       TS_ASSERT_EQUALS(1, mock->base00());
       TS_ASSERT_EQUALS(2, mock->base00());
       TS_ASSERT_EQUALS(3, mock->base00());
       TS_ASSERT_EQUALS(4, mock->base00());
       TS_ASSERT_EQUALS(5, mock->base00());
       TS_ASSERT_EQUALS(6, mock->base00());
       TS_ASSERT_EQUALS(7, mock->base00());
       TS_ASSERT_EQUALS(8, mock->base00());
       TS_ASSERT_EQUALS(9, mock->base00());
       TS_ASSERT_EQUALS(10, mock->base00());
       TS_ASSERT_EQUALS(11, mock->base00());
   }

   // throws()
   void testShouldBeAbleThrowAnException()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base00).stubs().will(increase(1, 3)).then(throws(10));

       TS_ASSERT_EQUALS(1, mock->base00());
       TS_ASSERT_EQUALS(2, mock->base00());
       TS_ASSERT_EQUALS(3, mock->base00());
       TS_ASSERT_THROWS_EQUALS(mock->base00(), int& e, e, 10);
   }

   // once()
   void testShouldBeAbleSpecifyInvokeOnce()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base00).expects(once()).will(returnValue(20));

       TS_ASSERT_EQUALS(20, mock->base00());
   }

   // once()
   void testShouldBeThrowExceptionIfInvokedTimesExceedsOnceButTheSpecifiedTimesIsOnce()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base00).expects(once()).will(returnValue(20));

       TS_ASSERT_EQUALS(20, mock->base00());

       TS_ASSERT_THROWS(mock->base00(), Exception);
   }

   // once()
   void testShouldBeThrowExceptionIfYouSpecifiedInvokingOnceButYouAcutallyDidNot()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base00).expects(once()).will(returnValue(20));

       TS_ASSERT_THROWS(mock.verify(), Exception);
   }

   // exactly()
   void testShouldBeAbleSpecifieExactInvokingTimes()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base00).expects(exactly(2)).will(returnValue(20));

       TS_ASSERT_EQUALS(20, mock->base00());
       TS_ASSERT_EQUALS(20, mock->base00());
   }

   // exactly()
   void testShouldBeThrowExceptionIfInvokedTimesExceedsSpecifiedTimes()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base00).expects(exactly(2)).will(returnValue(20));

       TS_ASSERT_EQUALS(20, mock->base00());
       TS_ASSERT_EQUALS(20, mock->base00());
       TS_ASSERT_EQUALS(20, mock->base00());

       TS_ASSERT_THROWS(mock.verify(), Exception);
   }

   // exactly()
   void testShouldBeThrowExceptionIfInvokedTimesLessThanSpecifiedTimes()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base00).expects(exactly(2)).will(returnValue(20));

       TS_ASSERT_EQUALS(20, mock->base00());

       TS_ASSERT_THROWS(mock.verify(), Exception);
   }

   // atLeast()
   void testShouldSupportSpecifyingAtLeastTimes()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base00).expects(atLeast(2)).will(returnValue(20));

       TS_ASSERT_EQUALS(20, mock->base00());
       TS_ASSERT_EQUALS(20, mock->base00());
       TS_ASSERT_EQUALS(20, mock->base00());
       TS_ASSERT_EQUALS(20, mock->base00());
   }

   // atLeast()
   void testShouldBeThrowExceptionIfInvokedTimesLessThanSpecifiedAtLeastTimes()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base00).expects(atLeast(2)).will(returnValue(20));

       TS_ASSERT_EQUALS(20, mock->base00());

       TS_ASSERT_THROWS(mock.verify(), Exception);
   }

   // atMost()
   void testShouldSupportSpecifyingAtMostTimes()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base00).expects(atMost(2)).will(returnValue(20));

       TS_ASSERT_EQUALS(20, mock->base00());
       TS_ASSERT_EQUALS(20, mock->base00());
   }

   // atMost()
   void testShouldSupportSpecifyingAtMostTimes1()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base00).expects(atMost(2)).will(returnValue(20));

       TS_ASSERT_EQUALS(20, mock->base00());
   }

   // atMost()
   void testShouldThrowExceptionIfInvokedTimesMoreThanSpecifiedAtLeastTimes()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base00).expects(atMost(2)).will(returnValue(20));

       TS_ASSERT_EQUALS(20, mock->base00());
       TS_ASSERT_EQUALS(20, mock->base00());
       TS_ASSERT_THROWS(((Interface*)mock)->base00(), Exception);
   }

   // never()
   void testShouldBeAbleToSpecifyNeverInvokeAnInvocation()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base00).expects(never());
   }

   // never()
   void testShouldThrowAnExceptionIfYouAreTryingToInvokeAnInvocationWhichWasSpecifedNeverInvoked()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base00).expects(never()).will(returnValue(20));

       TS_ASSERT_THROWS(mock->base00(), Exception);
   }

   // with()
   void testShouldBeAbleToSelectAppropriateInvocationToInvoke()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base01)
           .stubs()
           .with(eq(12))
           .will(returnValue(true));

       mock.method(&Interface::base01)
           .stubs()
           .with(eq(21))
           .will(returnValue(false));

       TS_ASSERT(mock->base01(12));
       TS_ASSERT(mock->base01(12));

       TS_ASSERT(!mock->base01(21));
       TS_ASSERT(!mock->base01(21));
   }

   // with()
   void testShouldThrowExceptionIfAnAppropriateInvocationWasNotSpecified()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base01)
           .stubs()
           .with(eq(12))
           .will(returnValue(true));

       mock.method(&Interface::base01)
           .stubs()
           .with(eq(21))
           .will(returnValue(false));

       TS_ASSERT_THROWS(mock->base01(16), Exception);
   }

   // startWith()
   void testShouldBeAbleToSelectAppropriateInvocationToInvokeByStartWith()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base11)
           .stubs()
           .with(startWith("abcd"))
           .will(returnValue((long)1));

       mock.method(&Interface::base11)
           .stubs()
           .with(startWith("1234"))
           .will(returnValue((long)2));

       TS_ASSERT_EQUALS(1, mock->base11("abcdefg"));
       TS_ASSERT_EQUALS(2, mock->base11("1234567"));
   }

   // before()
   void testShouldSupportBeforeOnOneObject()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base01)
           .expects(atLeast(1))
           .before("1")
           .with(eq(12))
           .will(returnValue(true));

       mock.method(&Interface::base01)
           .expects(atLeast(1))
           .with(eq(21))
           .will(returnValue(false))
           .id("1");

       TS_ASSERT(mock->base01(12));
       TS_ASSERT(mock->base01(12));

       TS_ASSERT(!mock->base01(21));
       TS_ASSERT(!mock->base01(21));
   }

   // before()
   void testShouldThrowAnExceptionIfYouDidNotInvokeTheOneFirstlyWhichYouSaidItShouldBeInvokedBeforeAnother()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base01)
           .expects(atLeast(1))
           .before("1")
           .with(eq(12))
           .will(returnValue(true));

       mock.method(&Interface::base01)
           .expects(atLeast(1))
           .with(eq(21))
           .will(returnValue(false))
           .id("1");

       TS_ASSERT(!mock->base01(21));

       TS_ASSERT_THROWS(mock->base01(12), Exception);
   }

   // before()
   void testShouldSupportBeforeOnDifferentObject()
   {
       MockObject<Interface> mock0;
       MockObject<Interface> mock1;

       mock0.method(&Interface::base01)
           .expects(atLeast(1))
           .before(mock1, "1")
           .with(eq(12))
           .will(returnValue(true));

       mock1.method(&Interface::base01)
           .expects(atLeast(1))
           .with(eq(12))
           .will(returnValue(false))
           .id("1");

       TS_ASSERT(mock0->base01(12));
       TS_ASSERT(!mock1->base01(12));
   }

   // before()
   void testShouldThrowAnExceptionIfYouDidNotInvokeTheOneFirstlyWhichYouSaidItShouldBeInvokedBeforeAnother1()
   {
       MockObject<Interface> mock0;
       MockObject<Interface> mock1;

       mock0.method(&Interface::base01)
           .expects(atLeast(1))
           .before(mock1, "1")
           .with(eq(12))
           .will(returnValue(true));

       mock1.method(&Interface::base01)
           .expects(atLeast(1))
           .with(eq(12))
           .will(returnValue(false))
           .id("1");

       TS_ASSERT(!mock1->base01(12));
       TS_ASSERT_THROWS(mock0->base01(12), Exception);
   }

   // before()
   void testShouldSupportMultipleBeforeSpecification()
   {
       MockObject<Interface> mock0;
       MockObject<Interface> mock1;
       MockObject<Interface> mock2;

       mock0.method(&Interface::base01)
           .expects(atLeast(1))
           .before(mock1, "1")
           .before(mock2, "1")
           .with(eq(12))
           .will(returnValue(true));

       mock1.method(&Interface::base01)
           .expects(atLeast(1))
           .with(eq(12))
           .will(returnValue(false))
           .id("1");

       mock2.method(&Interface::base01)
           .expects(atLeast(1))
           .with(eq(12))
           .will(returnValue(false))
           .id("1");

       TS_ASSERT(mock0->base01(12));
       TS_ASSERT(!mock1->base01(12));
       TS_ASSERT(!mock2->base01(12));
   }

   // before()
   void testShouldThrowExceptionIfAnyOfOrderDefinedInBeforeSpecifactionIsBroken()
   {
       MockObject<Interface> mock0;
       MockObject<Interface> mock1;
       MockObject<Interface> mock2;

       mock0.method(&Interface::base01)
           .expects(atLeast(1))
           .before(mock1, "1")
           .before(mock2, "1")
           .with(eq(12))
           .will(returnValue(true));

       mock1.method(&Interface::base01)
           .expects(atLeast(1))
           .with(eq(12))
           .will(returnValue(false))
           .id("1");

       mock2.method(&Interface::base01)
           .expects(atLeast(1))
           .with(eq(12))
           .will(returnValue(false))
           .id("1");

       TS_ASSERT(!mock1->base01(12));
       TS_ASSERT_THROWS(mock0->base01(12), Exception);
   }

   // before()
   void testShouldThrowExceptionIfAnyOfOrderDefinedInBeforeSpecifactionIsBroken1()
   {
       MockObject<Interface> mock0;
       MockObject<Interface> mock1;
       MockObject<Interface> mock2;

       mock0.method(&Interface::base01)
           .expects(atLeast(1))
           .before(mock1, "1")
           .before(mock2, "1")
           .with(eq(12))
           .will(returnValue(true));

       mock1.method(&Interface::base01)
           .expects(atLeast(1))
           .with(eq(12))
           .will(returnValue(false))
           .id("1");

       mock2.method(&Interface::base01)
           .expects(atLeast(1))
           .with(eq(12))
           .will(returnValue(false))
           .id("1");

       TS_ASSERT(!mock2->base01(12));
       TS_ASSERT_THROWS(mock0->base01(12), Exception);
   }

   // after()
   void testShouldSupportAfterOnOneObject()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base01)
           .expects(atLeast(1))
           .with(eq(12))
           .after("1")
           .will(returnValue(true));

       mock.method(&Interface::base01)
           .expects(atLeast(1))
           .with(eq(21))
           .will(returnValue(false))
           .id("1");

       TS_ASSERT(!mock->base01(21));
       TS_ASSERT(!mock->base01(21));

       TS_ASSERT(mock->base01(12));
       TS_ASSERT(mock->base01(12));
   }

   // after()
   void testShouldThrowAnExceptionIfYouHaveInvokedTheOneWhichYouSaidItShouldBeInvokedAfterAnother()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base01)
           .expects(atLeast(1))
           .with(eq(12))
           .after("1")
           .will(returnValue(true));

       mock.method(&Interface::base01)
           .expects(atLeast(1))
           .with(eq(21))
           .will(returnValue(false))
           .id("1");

       TS_ASSERT_THROWS(mock->base01(12), Exception);
   }

   // after()
   void testShouldSupportAfterOnDifferentObject()
   {
       MockObject<Interface> mock0;
       MockObject<Interface> mock1;

       mock0.method(&Interface::base01)
           .expects(atLeast(1))
           .with(eq(12))
           .after(mock1, "1")
           .will(returnValue(true));

       mock1.method(&Interface::base01)
           .expects(atLeast(1))
           .with(eq(12))
           .will(returnValue(false))
           .id("1");

       TS_ASSERT(!mock1->base01(12));
       TS_ASSERT(mock0->base01(12));
   }

   // after()
   void testShouldThrowAnExceptionIfYouHaveInvokedTheOneWhichYouSaidItShouldBeInvokedAfterAnother1()
   {
       MockObject<Interface> mock0;
       MockObject<Interface> mock1;

       mock0.method(&Interface::base01)
           .expects(atLeast(1))
           .with(eq(12))
           .after(mock1, "1")
           .will(returnValue(true));

       mock1.method(&Interface::base01)
           .expects(atLeast(1))
           .with(eq(12))
           .will(returnValue(false))
           .id("1");

       TS_ASSERT_THROWS(mock0->base01(12), Exception);
   }

   // after()
   void testShouldSupportSpecifyMultipleAfterConstraits()
   {
       MockObject<Interface> mock0;
       MockObject<Interface> mock1;
       MockObject<Interface> mock2;

       mock0.method(&Interface::base01)
           .expects(atLeast(1))
           .with(eq(12))
           .after(mock1, "1")
           .after(mock2, "1")
           .will(returnValue(true));

       mock1.method(&Interface::base01)
           .expects(atLeast(1))
           .with(eq(12))
           .will(returnValue(false))
           .id("1");

       mock2.method(&Interface::base01)
           .expects(atLeast(1))
           .with(eq(12))
           .will(returnValue(false))
           .id("1");

       TS_ASSERT(!mock1->base01(12));
       TS_ASSERT(!mock2->base01(12));
       TS_ASSERT(mock0->base01(12));
   }

   // after()
   void testShouldThrowExceptionIfInvocationOrderIsNotAsAfterSpecification()
   {
       MockObject<Interface> mock0;
       MockObject<Interface> mock1;
       MockObject<Interface> mock2;

       mock0.method(&Interface::base01)
           .expects(atLeast(1))
           .with(eq(12))
           .after(mock1, "1")
           .after(mock2, "1")
           .will(returnValue(true));

       mock1.method(&Interface::base01)
           .expects(atLeast(1))
           .with(eq(12))
           .will(returnValue(false))
           .id("1");

       mock2.method(&Interface::base01)
           .expects(atLeast(1))
           .with(eq(12))
           .will(returnValue(false))
           .id("1");

       TS_ASSERT(!mock1->base01(12));
       TS_ASSERT_THROWS(mock0->base01(12), Exception);
   }

   // after()
   void testShouldThrowExceptionIfInvocationOrderIsNotAsAfterSpecification1()
   {
       MockObject<Interface> mock0;
       MockObject<Interface> mock1;
       MockObject<Interface> mock2;

       mock0.method(&Interface::base01)
           .expects(atLeast(1))
           .with(eq(12))
           .after(mock1, "1")
           .after(mock2, "1")
           .will(returnValue(true));

       mock1.method(&Interface::base01)
           .expects(atLeast(1))
           .with(eq(12))
           .will(returnValue(false))
           .id("1");

       mock2.method(&Interface::base01)
           .expects(atLeast(1))
           .with(eq(12))
           .will(returnValue(false))
           .id("1");

       TS_ASSERT(!mock2->base01(12));
       TS_ASSERT_THROWS(mock0->base01(12), Exception);
   }

   // returnValue(ref)
   void testShouldBeAbleToSupportReturningReference()
   {
      MockObject<Interface> mock;

      mock.method(&Interface::a)
          .stubs()
          .will(returnValue(str));

      TS_ASSERT_EQUALS(std::string("abcdefg"), mock->a());
   }

};

