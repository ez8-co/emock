
#ifndef __MOCKCPP_STUB_CONTAINER_H
#define __MOCKCPP_STUB_CONTAINER_H

#include <mockcpp/mockcpp.h>

#include <string>

MOCKCPP_NS_START

struct Stub;
struct StubContainerImpl;

struct StubContainer
{
    StubContainer(const std::string& space);
    ~StubContainer();

    void addStub(Stub* stub);

    Stub* getStub() const;

    void reset();

    std::string toString() const;

private:

    StubContainerImpl* This;
};

MOCKCPP_NS_END

#endif

