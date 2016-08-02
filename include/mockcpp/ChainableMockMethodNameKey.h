
#ifndef __MOCKCPP_CHAINABLE_MOCK_METHOD_NAME_KEY_H
#define __MOCKCPP_CHAINABLE_MOCK_METHOD_NAME_KEY_H

#include <mockcpp/mockcpp.h>

#include <mockcpp/ChainableMockMethodKey.h>

#include <string>

MOCKCPP_NS_START

struct ChainableMockMethodNameKey
    : public ChainableMockMethodKey
{
   ChainableMockMethodNameKey(const std::string& name);

   bool equals(const ChainableMockMethodKey * const rhs) const;

   std::string& getMethodName() const;

private:
   std::string methodName;
};

MOCKCPP_NS_END

#endif

