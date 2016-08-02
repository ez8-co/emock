
#include <mockcpp/ExpectsMatcher.h>
#include <mockcpp/Invocation.h>

MOCKCPP_NS_START

ExpectsMatcher::ExpectsMatcher(Matcher* expectedMatcher)
   : matcher(expectedMatcher)
{
}

///////////////////////////////////////////////////////////
ExpectsMatcher::~ExpectsMatcher()
{
    delete matcher;
}

///////////////////////////////////////////////////////////
bool ExpectsMatcher::matches(const Invocation& inv) const 
{
    return matcher->matches(inv);
}

///////////////////////////////////////////////////////////
void ExpectsMatcher::increaseInvoked(const Invocation& inv)
{
    matcher->increaseInvoked(inv);
}

///////////////////////////////////////////////////////////
void ExpectsMatcher::verify()
{
    matcher->verify();
}

///////////////////////////////////////////////////////////
std::string ExpectsMatcher::toString() const
{
    oss_t oss;

    oss << ".expects(" << matcher->toString() << ")";

    return oss.str();
}

///////////////////////////////////////////////////////////

MOCKCPP_NS_END

