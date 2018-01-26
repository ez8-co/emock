
#include <emock/InvocationMockerNamespace.h>
#include <emock/InvocationMocker.h>
#include <emock/Method.h>
#include <emock/AfterMatcher.h>
#include <emock/PendingMatcher.h>

EMOCK_NS_START

//////////////////////////////////////////////////////////////////////
template <class Builder>
AfterMatchBuilder<Builder>&
AfterMatchBuilder<Builder>::after(const InvocationMockerNamespace& ns, const std::string& name)
{
    return after(&const_cast<InvocationMockerNamespace&>(ns), name);
}

//////////////////////////////////////////////////////////////////////
template <class Builder>
AfterMatchBuilder<Builder>&
AfterMatchBuilder<Builder>::after(InvocationMockerNamespace* ns, const std::string& id)
{
    getMocker()->addMatcher(
			new PendingMatcher(
				new AfterMatcher(),
				  ns, id, getMocker())); 
    return *this;
}

//////////////////////////////////////////////////////////////////////
template <class Builder>
AfterMatchBuilder<Builder>&
AfterMatchBuilder<Builder>::after(const std::string& name)
{
    return after(getMocker()->getMethod()->getNamespace(), name);
}

//////////////////////////////////////////////////////////////////////

EMOCK_NS_END


