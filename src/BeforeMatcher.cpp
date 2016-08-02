
#include <mockcpp/BeforeMatcher.h>
#include <mockcpp/InvocationMocker.h>
#include <mockcpp/Asserter.h>
#include <mockcpp/Invocation.h>
#include <mockcpp/InvocationId.h>
#include <mockcpp/ChainableMockMethodCore.h>

MOCKCPP_NS_START

//////////////////////////////////////////////////////
BeforeMatcher::BeforeMatcher()
	: previousCall(0)
{}

//////////////////////////////////////////////////////
bool BeforeMatcher::matches(const Invocation& inv) const
{
    return true;
}

//////////////////////////////////////////////////////
void BeforeMatcher::increaseInvoked(const Invocation& inv)
{
    oss_t oss;

    oss << "Expected invoked before the invocation with id \"" 
        << previousCall->getId()->getId()
        << "\", but that invocation has been invoked.";

    MOCKCPP_ASSERT_TRUE_MESSAGE(
         oss.str(),
         !previousCall->hasBeenInvoked());
}

//////////////////////////////////////////////////////
std::string BeforeMatcher::toString() const
{
    return "before";
}

//////////////////////////////////////////////////////
void BeforeMatcher::verify() 
{
}

//////////////////////////////////////////////////////
bool BeforeMatcher::isCompleted(void) const
{
    return previousCall != 0;
}

//////////////////////////////////////////////////////
void BeforeMatcher::setOrderingInvocationMocker(InvocationMocker* mocker)
{
    previousCall = mocker;
}

MOCKCPP_NS_END

