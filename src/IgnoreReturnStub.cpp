
#include <mockcpp/IgnoreReturnStub.h>
#include <mockcpp/Ignore.h>

MOCKCPP_NS_START

/////////////////////////////////////////////////////
IgnoreReturnStub::IgnoreReturnStub()
   : hasBeenInvoked(false)
{
}
/////////////////////////////////////////////////////
bool
IgnoreReturnStub::isCompleted() const
{
    return hasBeenInvoked;
}
/////////////////////////////////////////////////////
Any&
IgnoreReturnStub::invoke()
{
    hasBeenInvoked = true;
    return getIgnore();
}

/////////////////////////////////////////////////////
std::string IgnoreReturnStub::toString(void) const
{
    return "ignoreReturnValue()";
}

/////////////////////////////////////////////////////
const std::type_info& IgnoreReturnStub::type() const
{
    return typeid(Ignore);
}

/////////////////////////////////////////////////////

MOCKCPP_NS_END

