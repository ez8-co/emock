
#include <mockcpp/ReturnStub.h>

MOCKCPP_NS_START

/////////////////////////////////////////////////////
ReturnStub::ReturnStub(const Any& value)
		: returnValue(value), hasBeenInvoked(false)
{}

/////////////////////////////////////////////////////
bool ReturnStub::isCompleted() const
{
   return hasBeenInvoked;
}
/////////////////////////////////////////////////////
Any& ReturnStub::invoke(void)
{
    hasBeenInvoked = true;
    return returnValue;
}

/////////////////////////////////////////////////////
const std::type_info& ReturnStub::type() const
{
    return returnValue.type();
}

/////////////////////////////////////////////////////
std::string ReturnStub::toString(void) const
{
    return std::string("returnValue(") +
           returnValue.toTypeAndValueString() + 
           std::string(")");
}

MOCKCPP_NS_END

