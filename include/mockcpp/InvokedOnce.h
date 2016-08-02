
#ifndef __MOCKCPP_INVOKED_ONCE_H
#define __MOCKCPP_INVOKED_ONCE_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/InvocationTimesMatcher.h>

MOCKCPP_NS_START

struct InvokedOnce : public InvocationTimesMatcher
{
    InvokedOnce();

    bool matches(const Invocation& inv) const;
    void increaseInvoked(const Invocation& inv);

    void verify(void);

    std::string toString(void) const;
};

MOCKCPP_NS_END

#endif

