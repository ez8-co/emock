
#ifndef __MOCKCPP_DEFAULT_MATCHER_H
#define __MOCKCPP_DEFAULT_MATCHER_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/Matcher.h>

MOCKCPP_NS_START

struct Invocation;

struct DefaultMatcher : public Matcher
{
    bool matches(const Invocation& inv) const;
    void increaseInvoked(const Invocation& inv);
    void verify();
    std::string toString() const;
};

MOCKCPP_NS_END

#endif

