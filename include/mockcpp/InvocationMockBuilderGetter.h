
#ifndef __MOCKCPP_INVOCATION_MOCK_BUILDER_GETTER_H
#define __MOCKCPP_INVOCATION_MOCK_BUILDER_GETTER_H

#include <mockcpp/mockcpp.h>

#include <mockcpp/MockBuilder.h>
#include <mockcpp/StubsBuilder.h>
#include <mockcpp/DefaultBuilder.h>

MOCKCPP_NS_START

///////////////////////////////////////////////
struct Matcher;
struct InvocationMockerContainer;
struct Method;

///////////////////////////////////////////////
struct InvocationMockBuilderGetter
{
    InvocationMockBuilderGetter(InvocationMockerContainer* container, Method* method);
    ~InvocationMockBuilderGetter();

    StubsBuilder stubs(); 
    MockBuilder expects(Matcher* matcher); 
    DefaultBuilder defaults();

private:
    InvocationMockerContainer* invocationMockerContainer;
    Method* method;
};

///////////////////////////////////////////////

MOCKCPP_NS_END

#endif

