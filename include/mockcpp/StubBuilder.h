
#ifndef __MOCKCPP_STUB_BUILDER_H
#define __MOCKCPP_STUB_BUILDER_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/DummyBuilder.h>

MOCKCPP_NS_START

struct InvocationMocker;
struct Stub;

template <typename Builder = DummyBuilder >
struct StubBuilder : public Builder
{
    Builder& will(Stub* stub);

    virtual ~StubBuilder() {}

private:

    virtual InvocationMocker* getMocker() const = 0;
};

MOCKCPP_NS_END

#include <mockcpp/StubBuilder.tcc>

#endif

