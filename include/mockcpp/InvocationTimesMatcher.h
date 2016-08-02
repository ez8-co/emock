
#ifndef __MOCKCPP_INVOCATION_TIMES_MATCHER_H
#define __MOCKCPP_INVOCATION_TIMES_MATCHER_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/Matcher.h>

MOCKCPP_NS_START

struct InvokedTimesReader;
struct Invocation;

struct InvocationTimesMatcher : public Matcher
{
    InvocationTimesMatcher();
    ~InvocationTimesMatcher();

    void increaseInvoked(const Invocation& inv);

    void setInvokedTimesReader(InvokedTimesReader* recorder);

protected:

    unsigned int getInvokedTimes() const;

private:

    InvokedTimesReader* invokedTimesReader;
};

MOCKCPP_NS_END

#endif

