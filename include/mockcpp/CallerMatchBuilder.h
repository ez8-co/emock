
#ifndef __MOCKCPP_CALLER_MATCH_BUILDER_H
#define __MOCKCPP_CALLER_MATCH_BUILDER_H

#include <mockcpp/mockcpp.h>

#include <mockcpp/DummyBuilder.h>

#include <string>

MOCKCPP_NS_START

struct InvocationMocker;

template <typename Builder = DummyBuilder >
struct CallerMatchBuilder : public Builder
{
   Builder& caller(const std::string& nameOfCaller);

   virtual ~CallerMatchBuilder() {}

private:

   virtual InvocationMocker* getMocker() const = 0;
};

MOCKCPP_NS_END

#include <mockcpp/CallerMatchBuilder.tcc>

#endif
