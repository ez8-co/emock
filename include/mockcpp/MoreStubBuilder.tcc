
#include <mockcpp/InvocationMocker.h>
#include <mockcpp/ThenStub.h>

MOCKCPP_NS_START

template<class Builder>
MoreStubBuilder<Builder>&
MoreStubBuilder<Builder>::then(Stub* stub)
{
    getMocker()->addStub(new ThenStub(stub));
    return *this;
}

MOCKCPP_NS_END

