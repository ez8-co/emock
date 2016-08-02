/***
   mockcpp is a C/C++ mock framework.
   Copyright [2008] [Darwin Yuan <darwin.yuan@gmail.com>]

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
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

