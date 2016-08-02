
#ifndef __MOCKCPP_STATELESS_MATCHER_H
#define __MOCKCPP_STATELESS_MATCHER_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/Matcher.h>

MOCKCPP_NS_START

struct Invocation;

struct StatelessMatcher : public Matcher
{
    virtual ~StatelessMatcher() {}
    virtual bool matches(const Invocation& inv) const = 0;
    virtual void increaseInvoked(const Invocation& inv) {}
};

MOCKCPP_NS_END

#endif

