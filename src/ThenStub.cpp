
#include <mockcpp/OutputStringStream.h>
#include <mockcpp/ThenStub.h>

MOCKCPP_NS_START

//////////////////////////////////////////////
ThenStub::ThenStub(Stub* stub)
	: expectedStub(stub)
{
}

//////////////////////////////////////////////
ThenStub::~ThenStub()
{
    delete expectedStub;
}

//////////////////////////////////////////////
bool ThenStub::isCompleted() const
{
    return expectedStub->isCompleted();
}

//////////////////////////////////////////////
Any& ThenStub::invoke(const Invocation& inv)
{
    return expectedStub->invoke(inv);
}
    
//////////////////////////////////////////////
std::string ThenStub::toString() const
{
    oss_t oss;

    oss << ".then(" << expectedStub->toString() << ")";

    return oss.str();
}

MOCKCPP_NS_END


