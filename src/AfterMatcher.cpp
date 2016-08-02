
#include <mockcpp/AfterMatcher.h>
#include <mockcpp/InvocationMocker.h>
#include <mockcpp/Asserter.h>
#include <mockcpp/Invocation.h>
#include <mockcpp/InvocationId.h>
#include <mockcpp/ChainableMockMethodCore.h>

MOCKCPP_NS_START

//////////////////////////////////////////////////////
AfterMatcher::AfterMatcher()
    : previousCall(0)
{}
//////////////////////////////////////////////////////
bool AfterMatcher::matches(const Invocation& inv) const
{
    return true;
}

//////////////////////////////////////////////////////
void AfterMatcher::increaseInvoked(const Invocation& inv)
{
    oss_t oss;

    oss << "Expected invoked after the invocation with id \""
        << previousCall->getId()->getId()
        << "\", but that invocation has NOT been invoked yet.";

    MOCKCPP_ASSERT_TRUE_MESSAGE(
         oss.str(), 
         previousCall->hasBeenInvoked());
}

//////////////////////////////////////////////////////
std::string AfterMatcher::toString() const
{
    return "after";
}

//////////////////////////////////////////////////////
void AfterMatcher::verify() 
{
}

//////////////////////////////////////////////////////
bool AfterMatcher::isCompleted(void) const
{
    return previousCall != 0;
}

//////////////////////////////////////////////////////
void AfterMatcher::setOrderingInvocationMocker(InvocationMocker* mocker)
{
    previousCall = mocker;
}

MOCKCPP_NS_END

