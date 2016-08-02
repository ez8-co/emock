
#include <mockcpp/OutputStringStream.h>
#include <mockcpp/InvokedAtLeast.h>
#include <mockcpp/Asserter.h>
#include <mockcpp/Formatter.h>

MOCKCPP_NS_START

///////////////////////////////////////////////////////
InvokedAtLeast::InvokedAtLeast(const unsigned int times)
   : lowLimit(times)
{
}

///////////////////////////////////////////////////////
bool InvokedAtLeast::matches(const Invocation& inv) const
{
	return true;
}

///////////////////////////////////////////////////////
std::string InvokedAtLeast::toString(void) const
{
    oss_t oss;

    oss << "atLeast(" << lowLimit << ")";

    return oss.str();
}

///////////////////////////////////////////////////////
void InvokedAtLeast::verify(void)
{
    oss_t oss;

    oss << "Expected at least " << lowLimit
        << " times, but it's actually invoked " << getInvokedTimes() << " times";

    MOCKCPP_ASSERT_TRUE_MESSAGE(
			"Invoked too few times" 
         , getInvokedTimes() >= lowLimit);
}

MOCKCPP_NS_END


