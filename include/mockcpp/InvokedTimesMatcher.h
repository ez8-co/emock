
#ifndef __MOCKCPP_INVOKED_TIMES_MATCHER_H
#define __MOCKCPP_INVOKED_TIMES_MATCHER_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/Matcher.h>

MOCKCPP_NS_START

struct InvokedTimesRecorder;
struct Invocation;

struct InvokedTimesMatcher : public Matcher
{
    InvokedTimesMatcher(InvokedTimesRecorder* recorder);

    ~InvokedTimesMatcher();

    bool matches(const Invocation& inv) const;

    void increaseInvoked(const Invocation& inv);

    std::string toString(void) const;

    void verify();

private:

    InvokedTimesRecorder* invokedTimesRecorder;
};

MOCKCPP_NS_END

#endif

