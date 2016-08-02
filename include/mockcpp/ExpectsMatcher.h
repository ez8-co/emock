
#ifndef __MOCKCPP_EXPECTS_MATCHER_H
#define __MOCKCPP_EXPECTS_MATCHER_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/Matcher.h>

MOCKCPP_NS_START

struct Invocation;
struct Matcher;

struct ExpectsMatcher : public Matcher
{
    ExpectsMatcher(Matcher*);
    ~ExpectsMatcher();

    bool matches(const Invocation& inv) const;
    void increaseInvoked(const Invocation& inv);
    void verify();
    std::string toString() const;

private:

    Matcher* matcher;
};

MOCKCPP_NS_END

#endif

