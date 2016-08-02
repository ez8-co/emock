
#ifndef __MOCKCPP_BEFORE_MATCH_BUILDER_H
#define __MOCKCPP_BEFORE_MATCH_BUILDER_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/DummyBuilder.h>

MOCKCPP_NS_START

struct InvocationMockerNamespace;
struct InvocationMocker;

template < typename Builder = DummyBuilder >
struct BeforeMatchBuilder : public Builder
{
    BeforeMatchBuilder&
	 before(const InvocationMockerNamespace& ns, const std::string& name);

    BeforeMatchBuilder&
	 before(InvocationMockerNamespace* ns, const std::string& name);

    BeforeMatchBuilder&
	 before(const std::string& name);

    virtual ~BeforeMatchBuilder() {}

private:

    void
    setupOrderingBeforeMatchers(InvocationMocker* mocker);

private:

    virtual InvocationMocker* getMocker() const = 0;
};

MOCKCPP_NS_END

#include <mockcpp/BeforeMatchBuilder.tcc>

#endif

