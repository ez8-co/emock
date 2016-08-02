
#include <mockcpp/InvocationMockerNamespace.h>
#include <mockcpp/InvocationMocker.h>
#include <mockcpp/Method.h>
#include <mockcpp/AfterMatcher.h>
#include <mockcpp/PendingMatcher.h>

MOCKCPP_NS_START

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

MOCKCPP_NS_END


