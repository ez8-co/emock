
#include <mockcpp/InvocationMockerNamespace.h>
#include <mockcpp/InvocationMocker.h>
#include <mockcpp/Method.h>
#include <mockcpp/BeforeMatcher.h>
#include <mockcpp/PendingMatcher.h>

MOCKCPP_NS_START

//////////////////////////////////////////////////////////////////////
template <class Builder>
BeforeMatchBuilder<Builder>&
BeforeMatchBuilder<Builder>::before(const InvocationMockerNamespace& ns, const std::string& name)
{
    return before(&const_cast<InvocationMockerNamespace&>(ns), name);
}

//////////////////////////////////////////////////////////////////////
template <class Builder>
BeforeMatchBuilder<Builder>&
BeforeMatchBuilder<Builder>::before(InvocationMockerNamespace* ns, const std::string& id)
{
    getMocker()->addMatcher(
			new PendingMatcher(
				new BeforeMatcher(),
               ns , id , getMocker()));

    return *this;
}

//////////////////////////////////////////////////////////////////////
template <class Builder>
BeforeMatchBuilder<Builder>&
BeforeMatchBuilder<Builder>::before(const std::string& name)
{
    return before(getMocker()->getMethod()->getNamespace(), name);
}

//////////////////////////////////////////////////////////////////////

MOCKCPP_NS_END


