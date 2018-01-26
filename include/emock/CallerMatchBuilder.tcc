
#include <emock/InvocationMocker.h>
#include <emock/CallerMatcher.h>


EMOCK_NS_START


//////////////////////////////////////////////////////////////////////
template <class Builder>
Builder&
CallerMatchBuilder<Builder>::caller(const std::string& nameOfCaller)
{
    getMocker()->addMatcher(new CallerMatcher(nameOfCaller)); 
    return *this;
}

//////////////////////////////////////////////////////////////////////

EMOCK_NS_END
