
#include <mockcpp/StubsMatcher.h>
#include <mockcpp/Invocation.h>

MOCKCPP_NS_START

///////////////////////////////////////////////////////////
bool StubsMatcher::matches(const Invocation& inv) const 
{
    return true;
}

///////////////////////////////////////////////////////////
void StubsMatcher::increaseInvoked(const Invocation& inv)
{
}

///////////////////////////////////////////////////////////
void StubsMatcher::verify()
{
}

///////////////////////////////////////////////////////////
std::string StubsMatcher::toString() const
{
    return ".stubs()";
}

MOCKCPP_NS_END

