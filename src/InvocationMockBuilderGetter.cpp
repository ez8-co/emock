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

#include <mockcpp/InvocationMockBuilderGetter.h>
#include <mockcpp/InvocationMockerContainer.h>
#include <mockcpp/StubsMatcher.h>
#include <mockcpp/ExpectsMatcher.h>
#include <mockcpp/InvokedTimesMatcher.h>
#include <mockcpp/InvocationTimesMatcher.h>
#include <mockcpp/InvokedTimesRecorder.h>
#include <mockcpp/SimpleInvocationRecorder.h>
#include <mockcpp/InvocationMocker.h>
#include <mockcpp/DefaultMatcher.h>
#include <mockcpp/Method.h>

MOCKCPP_NS_START

///////////////////////////////////////////////////////////
InvocationMockBuilderGetter::
InvocationMockBuilderGetter(InvocationMockerContainer* container, Method* m)
	: invocationMockerContainer(container), method(m)
{

}
///////////////////////////////////////////////////////////
InvocationMockBuilderGetter::~InvocationMockBuilderGetter()
{
}

//////////////////////////////////////////////////////////
StubsBuilder InvocationMockBuilderGetter::stubs()
{
    InvocationMocker* mocker = new InvocationMocker(method);
    mocker->addMatcher(new StubsMatcher);
    mocker->addMatcher(new InvokedTimesMatcher(new SimpleInvocationRecorder));

    invocationMockerContainer->addInvocationMocker(mocker);

    return StubsBuilder(mocker);
}

//////////////////////////////////////////////////////////
MockBuilder InvocationMockBuilderGetter::expects(Matcher* matcher)
{
    InvocationMocker* mocker = new InvocationMocker(method);

    InvokedTimesRecorder* recorder = new SimpleInvocationRecorder;
    InvocationTimesMatcher* itMatcher = dynamic_cast<InvocationTimesMatcher*>(matcher);
    if (itMatcher != 0)
    {
      itMatcher->setInvokedTimesReader(recorder);
    }

    mocker->addMatcher(new ExpectsMatcher(matcher));
    mocker->addMatcher(new InvokedTimesMatcher(recorder));

    invocationMockerContainer->addInvocationMocker(mocker);

    return MockBuilder(mocker);
}

//////////////////////////////////////////////////////////
DefaultBuilder InvocationMockBuilderGetter::defaults()
{
    InvocationMocker* mocker = new InvocationMocker(method);
    mocker->addMatcher(new DefaultMatcher);

    invocationMockerContainer->addDefaultInvocationMocker(mocker);

    return DefaultBuilder(mocker);
}

//////////////////////////////////////////////////////////

MOCKCPP_NS_END

