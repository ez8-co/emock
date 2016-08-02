
#include <mockcpp/OutputStringStream.h>
#include <mockcpp/InvokedTimesMatcher.h>
#include <mockcpp/InvokedTimesRecorder.h>

MOCKCPP_NS_START

///////////////////////////////////////////////////////////////////////
InvokedTimesMatcher::InvokedTimesMatcher(InvokedTimesRecorder* recorder)
    : invokedTimesRecorder(recorder)
{
}

///////////////////////////////////////////////////////////////////////
InvokedTimesMatcher::~InvokedTimesMatcher()
{
    delete invokedTimesRecorder;
}

///////////////////////////////////////////////////////////////////////
bool InvokedTimesMatcher::matches(const Invocation& inv) const
{
    return true;
}

///////////////////////////////////////////////////////////////////////
void InvokedTimesMatcher::increaseInvoked(const Invocation& inv)
{
    invokedTimesRecorder->increaseInvoked();
}

///////////////////////////////////////////////////////////////////////
std::string InvokedTimesMatcher::toString(void) const
{
    oss_t oss;

    oss << ".invoked(" << invokedTimesRecorder->getInvokedTimes() << ")";

    return oss.str();
}

///////////////////////////////////////////////////////////////////////
void InvokedTimesMatcher::verify()
{
}

///////////////////////////////////////////////////////////////////////

MOCKCPP_NS_END

