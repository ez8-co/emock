
#include <emock/InvocationMocker.h>

EMOCK_NS_START

//////////////////////////////////////////////////////
template <class Builder>
InvocationMockBuilder<Builder>::InvocationMockBuilder(InvocationMocker* mocker)
	: invocationMocker(mocker)
{
}

//////////////////////////////////////////////////////
template <class Builder>
InvocationMocker*
InvocationMockBuilder<Builder>::getMocker() const
{
    return invocationMocker;
}

EMOCK_NS_END


