#ifndef __MOCKCPP_CHAINABLE_MOCK_METHOD_CONTAINER_H
#define __MOCKCPP_CHAINABLE_MOCK_METHOD_CONTAINER_H

#include <mockcpp/mockcpp.h>

#include <string>

MOCKCPP_NS_START

struct ChainableMockMethodContainerImpl;
struct ChainableMockMethodKey;
struct ChainableMockMethodCore;
struct InvocationMocker;

///////////////////////////////////////////////////////////////
struct ChainableMockMethodContainer
{
    ChainableMockMethodContainer();
    ~ChainableMockMethodContainer();

    ChainableMockMethodCore* getMethod(ChainableMockMethodKey* key) const;
    void addMethod(ChainableMockMethodKey* key, ChainableMockMethodCore* method);

    InvocationMocker* findInvocationMocker(const std::string& id) const;

    void reset();
    void verify();

private:
    ChainableMockMethodContainerImpl* This;
};

MOCKCPP_NS_END

#endif

