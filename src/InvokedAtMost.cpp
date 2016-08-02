
#include <mockcpp/OutputStringStream.h>
#include <mockcpp/InvokedAtMost.h>
#include <mockcpp/Asserter.h>
#include <mockcpp/Formatter.h>

MOCKCPP_NS_START

InvokedAtMost::InvokedAtMost(const unsigned int times)
   : highLimit(times)
{
}

///////////////////////////////////////////////////////
bool InvokedAtMost::matches(const Invocation& inv) const
{
	return true;
}

///////////////////////////////////////////////////////
void InvokedAtMost::increaseInvoked(const Invocation& inv)
{
    oss_t oss;

    oss << "Expected at most " << highLimit 
        << " times, but you are trying to invoke more than that.";

    MOCKCPP_ASSERT_TRUE_MESSAGE(
         oss.str(), getInvokedTimes() < highLimit);
}

///////////////////////////////////////////////////////
std::string InvokedAtMost::toString(void) const
{
	 oss_t oss;

    oss << "atMost(" << highLimit << ")";

    return oss.str();
}

///////////////////////////////////////////////////////
void InvokedAtMost::verify(void)
{
// We won't need to verify it here, it was checked at runtime.
#if 0
    oss_t oss;
    
    oss << "Expected at most " << highLimit 
        << " times, but it's actually invoked " << getInvokedTimes() << " times";

    MOCKCPP_ASSERT_TRUE_MESSAGE(
			oss.str(),
         getInvokedTimes() <= highLimit);
#endif
}

MOCKCPP_NS_END


