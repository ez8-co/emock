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
#include <mockcpp/InvocationMocker.h>
#include <mockcpp/Invocation.h>
#include <mockcpp/InvocationMockBuilder.h>
#include <mockcpp/ChainingMockHelper.h>
#include <mockcpp/types/Any.h>
#include <mockcpp/InvokedTimesRecorder.h>

USING_MOCKCPP_NS

class TestInvocationMocker : public TESTCPP_NS::TestFixture
{
public:
	void setUp() { }
	void tearDown() { }

	/////////////////////////////////////////////////////////

	void testShouldReturnSettedStubWhenCallingInvoke()
	{
		InvocationMocker mocker(0);
		Invocation inv(__FUNCTION__);

		mocker.addStub(returnValue(10));

		TS_ASSERT(10 == any_cast<int>(mocker.invoke(inv)));
	}

	void testShouldSetInvokedStateAfterItsInvoked()
	{
		InvocationMocker mocker(0);
		Invocation inv(__FUNCTION__);

		TS_ASSERT(!mocker.hasBeenInvoked());
		mocker.invoke(inv);
		TS_ASSERT(mocker.hasBeenInvoked());
	}

};

