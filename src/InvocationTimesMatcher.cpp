
#include <mockcpp/InvocationTimesMatcher.h>
#include <mockcpp/InvokedTimesReader.h>

MOCKCPP_NS_START

/////////////////////////////////////////////////////////////////////
InvocationTimesMatcher::InvocationTimesMatcher()
    : invokedTimesReader(0)
{
}

/////////////////////////////////////////////////////////////////////
InvocationTimesMatcher::~InvocationTimesMatcher()
{
    //delete invokedTimesReader;
}

/////////////////////////////////////////////////////////////////////
void InvocationTimesMatcher::setInvokedTimesReader(InvokedTimesReader* reader)
{
    invokedTimesReader = reader;
}

/////////////////////////////////////////////////////////////////////
void InvocationTimesMatcher::increaseInvoked(const Invocation& inv)
{
}

/////////////////////////////////////////////////////////////////////
unsigned int InvocationTimesMatcher::getInvokedTimes() const
{
    return invokedTimesReader?invokedTimesReader->getInvokedTimes():0;
}

MOCKCPP_NS_END


