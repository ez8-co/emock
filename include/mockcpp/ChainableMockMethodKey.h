
#ifndef __MOCKCPP_CHAINABLE_MOCK_METHOD_KEY_H
#define __MOCKCPP_CHAINABLE_MOCK_METHOD_KEY_H

#include <mockcpp/mockcpp.h>

MOCKCPP_NS_START

struct ChainableMockMethodKey
{
    virtual bool equals(const ChainableMockMethodKey * const rhs) const = 0;

    virtual ~ChainableMockMethodKey() {}
};

MOCKCPP_NS_END

#endif

