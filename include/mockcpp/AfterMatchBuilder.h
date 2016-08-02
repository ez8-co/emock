
#ifndef __MOCKCPP_AFTER_MATCH_BUILDER_H
#define __MOCKCPP_AFTER_MATCH_BUILDER_H

#include <mockcpp/mockcpp.h>

#include <mockcpp/DummyBuilder.h>

MOCKCPP_NS_START

struct InvocationMockerNamespace;
struct InvocationMocker;

template <typename Builder = DummyBuilder>
struct AfterMatchBuilder : public Builder
{
    AfterMatchBuilder&
    after(const InvocationMockerNamespace& ns, const std::string& name);

    AfterMatchBuilder&
    after(InvocationMockerNamespace* ns, const std::string& name);

    AfterMatchBuilder&
    after(const std::string& name);

    virtual ~AfterMatchBuilder() {}

private:
    void
    setupOrderingAfterMatchers(InvocationMocker* mocker);
    
private:
    virtual InvocationMocker* getMocker() const = 0;
};

MOCKCPP_NS_END

#include <mockcpp/AfterMatchBuilder.tcc>

#endif

