
#include <mockcpp/InvocationMocker.h>

MOCKCPP_NS_START

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

MOCKCPP_NS_END


