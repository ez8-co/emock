
#include <mockcpp/InvocationMocker.h>
#include <mockcpp/WillStub.h>

MOCKCPP_NS_START

template<class Builder>
Builder& StubBuilder<Builder>::will(Stub* stub)
{
    getMocker()->addStub(new WillStub(stub));
    return *this;
}

MOCKCPP_NS_END


