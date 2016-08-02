
#include <mockcpp/DefaultMatcher.h>
#include <mockcpp/Invocation.h>

MOCKCPP_NS_START

///////////////////////////////////////////////////////////
bool DefaultMatcher::matches(const Invocation& inv) const 
{
    return true;
}

///////////////////////////////////////////////////////////
void DefaultMatcher::increaseInvoked(const Invocation& inv)
{
}

///////////////////////////////////////////////////////////
void DefaultMatcher::verify()
{
}

///////////////////////////////////////////////////////////
std::string DefaultMatcher::toString() const
{
    return ".defaults()";
}

MOCKCPP_NS_END

