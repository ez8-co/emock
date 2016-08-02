
#include <mockcpp/OutputStringStream.h>
#include <mockcpp/InvokedExactly.h>
#include <mockcpp/Asserter.h>
#include <mockcpp/Formatter.h>

MOCKCPP_NS_START

/////////////////////////////////////////////////////////
InvokedExactly::InvokedExactly(const unsigned int times)
   : expectedInvokedTimes(times)
{
}

/////////////////////////////////////////////////////////
bool InvokedExactly::matches(const Invocation& inv) const
{

    return true;
}

/////////////////////////////////////////////////////////
std::string
InvokedExactly::toString(void) const
{
	 oss_t ss;

    ss << "exactly(" << expectedInvokedTimes << ")";

    return ss.str();
}

/////////////////////////////////////////////////////////
void InvokedExactly::verify(void)
{
	 oss_t oss;

    oss << "Expected invoking exactly " << expectedInvokedTimes 
        << " times, but it's actually invoked " << getInvokedTimes() 
        << " times.";

    MOCKCPP_ASSERT_TRUE_MESSAGE(
         oss.str(),
         getInvokedTimes() == expectedInvokedTimes );
}

MOCKCPP_NS_END


