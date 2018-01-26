
#include <emock/InvocationMocker.h>
#include <emock/WillStub.h>
#include <emock/ThenStub.h>

EMOCK_NS_START

template<class Builder>
MoreStubBuilder<Builder>&
MoreStubBuilder<Builder>::then(Stub* stub)
{
    getMocker()->addStub(new ThenStub(stub));
    return *this;
}

template<class Builder>
MoreStubBuilder<Builder>&
StubBuilder<Builder>::will(Stub* stub)
{
    getMocker()->addStub(new WillStub(stub));
    return *this;
}

EMOCK_NS_END


