
#ifndef __MOCKCPP_MATCHER_H
#define __MOCKCPP_MATCHER_H

#include <mockcpp/mockcpp.h>
#include <string>

MOCKCPP_NS_START

struct Invocation;

struct Matcher
{
    virtual bool matches(const Invocation& inv) const = 0;
    virtual void increaseInvoked(const Invocation& inv) = 0;
    virtual void verify() = 0;
    virtual std::string toString() const = 0;

    virtual ~Matcher() {}
};

MOCKCPP_NS_END

#endif

