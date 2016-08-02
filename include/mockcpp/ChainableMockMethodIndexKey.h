
#ifndef __MOCKCPP_CHAINABLE_MOCK_METHOD_INDEX_KEY_H
#define __MOCKCPP_CHAINABLE_MOCK_METHOD_INDEX_KEY_H

#include <mockcpp/mockcpp.h>

#include <mockcpp/ChainableMockMethodKey.h>

#include <string>

MOCKCPP_NS_START

struct ChainableMockMethodIndexKey
    : public ChainableMockMethodKey
{
   ChainableMockMethodIndexKey(unsigned int vptrIndex, unsigned int vtblIndex);

   bool equals(const ChainableMockMethodKey * const rhs) const;

   unsigned int getIndex() const;

private:
   unsigned int index;
};

MOCKCPP_NS_END

#endif

