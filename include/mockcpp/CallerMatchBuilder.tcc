
#include <mockcpp/InvocationMocker.h>
#include <mockcpp/CallerMatcher.h>


MOCKCPP_NS_START


//////////////////////////////////////////////////////////////////////
template <class Builder>
Builder&
CallerMatchBuilder<Builder>::caller(const std::string& nameOfCaller)
{
    getMocker()->addMatcher(new CallerMatcher(nameOfCaller)); 
    return *this;
}

//////////////////////////////////////////////////////////////////////

MOCKCPP_NS_END
