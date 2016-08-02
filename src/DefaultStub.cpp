
#include <mockcpp/OutputStringStream.h>
#include <mockcpp/DefaultStub.h>

MOCKCPP_NS_START

//////////////////////////////////////////////
DefaultStub::DefaultStub(Stub* stub)
	: defaultStub(stub)
{
}

//////////////////////////////////////////////
DefaultStub::~DefaultStub()
{
    delete defaultStub;
}

//////////////////////////////////////////////
Any& DefaultStub::invoke(const Invocation& inv)
{
    return defaultStub->invoke(inv);
}
    
//////////////////////////////////////////////
std::string DefaultStub::toString() const
{
    oss_t oss;

    oss << "setDefaultStub(" << defaultStub->toString() << ")";

    return oss.str();
}

//////////////////////////////////////////////

MOCKCPP_NS_END


