
#include <mockcpp/OutputStringStream.h>
#include <mockcpp/CallerMatcher.h>
#include <mockcpp/Invocation.h>

MOCKCPP_NS_START

///////////////////////////////////////////////////////////
CallerMatcher::CallerMatcher(const std::string& name)
    : nameOfCaller(name)
{
}

///////////////////////////////////////////////////////////
bool CallerMatcher::matches(const Invocation& inv) const 
{
    return inv.getNameOfCaller() == nameOfCaller;
}

///////////////////////////////////////////////////////////
void CallerMatcher::increaseInvoked(const Invocation& inv)
{
}

///////////////////////////////////////////////////////////
void CallerMatcher::verify()
{
}

///////////////////////////////////////////////////////////
std::string CallerMatcher::toString() const
{
    oss_t oss;

    oss << ".caller(" << nameOfCaller << ")";

    return oss.str();
}

MOCKCPP_NS_END

