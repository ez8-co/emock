
#ifndef __MOCKCPP_MORE_STUB_BUILDER_H
#define __MOCKCPP_MORE_STUB_BUILDER_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/DummyBuilder.h>

MOCKCPP_NS_START

struct InvocationMocker;
struct Stub;

template <typename Builder = DummyBuilder >
struct MoreStubBuilder : public Builder
{
    MoreStubBuilder& then(Stub* stub);

    virtual ~MoreStubBuilder() {}

private:
    virtual InvocationMocker* getMocker() const = 0;
};

MOCKCPP_NS_END

#include <mockcpp/MoreStubBuilder.tcc>

#endif


