
#include <mockcpp/InvokedOnce.h>
#include <mockcpp/Asserter.h>
#include <mockcpp/OutputStringStream.h>

MOCKCPP_NS_START

///////////////////////////////////////////////////////
InvokedOnce::InvokedOnce()
{
}

///////////////////////////////////////////////////////
bool InvokedOnce::matches(const Invocation& inv) const
{
    return true;
}

///////////////////////////////////////////////////////
void InvokedOnce::increaseInvoked(const Invocation& inv)
{
    oss_t oss;

    oss << "Invocation is expected only once(), but you are trying to "
        << "invoke more than that";

    MOCKCPP_ASSERT_TRUE_MESSAGE(
         oss.str(), getInvokedTimes() < 1);
   
}
///////////////////////////////////////////////////////
std::string
InvokedOnce::toString(void) const
{
    return "once()";
}

///////////////////////////////////////////////////////
void InvokedOnce::verify(void)
{
    oss_t oss;

    oss << "Invocation is expected only once(), but it's been invoked "
        << getInvokedTimes() << " times";

    MOCKCPP_ASSERT_TRUE_MESSAGE(
         oss.str(), getInvokedTimes() == 1);
}

MOCKCPP_NS_END


