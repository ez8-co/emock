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
#include <mockcpp/Stub.h>
#include <mockcpp/StubContainer.h>
#include <mockcpp/Invocation.h>
#include <mockcpp/types/Any.h>


USING_MOCKCPP_NS

class TestStubContainer : public TESTCPP_NS::TestFixture
{
   struct TestStub : public Stub
   {
       TestStub(unsigned int maxTimes) 
         : times(0), limit(maxTimes) {}

       bool isCompleted() const
       { return times >= limit; }

       Any& invoke(const Invocation& inv)
       { times++; return any; }
    
       std::string toString() const
       { return ""; }

   private:

       Any any;
       unsigned int times;
       unsigned int limit;
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

	void testShouldBeAbleToGetAddedStub()
	{
       StubContainer container("");
       Invocation inv("", 0, 1);

       Stub* stub0 = new TestStub(1);
       Stub* stub1 = new TestStub(1);

       container.addStub(stub0);
       container.addStub(stub1);
       
       TS_ASSERT_EQUALS(container.getStub(), stub0);
       stub0->invoke(inv);
       TS_ASSERT_EQUALS(container.getStub(), stub1);
       stub1->invoke(inv);
   }

	void testShouldAlwaysReturnAStubBeforeItIsCompleted()
	{
       StubContainer container("");
       Invocation inv("", 0, 1);

       Stub* stub0 = new TestStub(3);
       Stub* stub1 = new TestStub(1);

       container.addStub(stub0);
       container.addStub(stub1);
       
       TS_ASSERT_EQUALS(container.getStub(), stub0);
       stub0->invoke(inv);
       TS_ASSERT_EQUALS(container.getStub(), stub0);
       stub0->invoke(inv);
       TS_ASSERT_EQUALS(container.getStub(), stub0);
       stub0->invoke(inv);

       TS_ASSERT_EQUALS(container.getStub(), stub1);
       stub1->invoke(inv);
   }

	void testShouldAlwaysReturnLastStubIfAllStubsHaveBeenReturnedEvenIfItHasBeenCompleted()
	{
       StubContainer container("");
       Invocation inv("", 0, 1);

       Stub* stub0 = new TestStub(1);
       Stub* stub1 = new TestStub(1);

       container.addStub(stub0);
       container.addStub(stub1);
       
       TS_ASSERT_EQUALS(container.getStub(), stub0);
       stub0->invoke(inv);

       TS_ASSERT_EQUALS(container.getStub(), stub1);
       stub1->invoke(inv);

       TS_ASSERT_EQUALS(container.getStub(), stub1);
       stub1->invoke(inv);

       TS_ASSERT_EQUALS(container.getStub(), stub1);
       stub1->invoke(inv);

       TS_ASSERT_EQUALS(container.getStub(), stub1);
       stub1->invoke(inv);
   }

   void testShouldReturnNullIfNoStubWasAdded()
   {
       StubContainer container("");
       
       TS_ASSERT(container.getStub() == 0);
   }
};

