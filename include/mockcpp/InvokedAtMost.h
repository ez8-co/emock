
#ifndef __MOCKCPP_INVOKED_ATMOST_H
#define __MOCKCPP_INVOKED_ATMOST_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/InvocationTimesMatcher.h>

MOCKCPP_NS_START

struct InvokedAtMost
    : public InvocationTimesMatcher
{
    InvokedAtMost(const unsigned int times);

    bool matches(const Invocation& inv) const;
    void increaseInvoked(const Invocation& inv);

    void verify(void);

    std::string toString(void) const;

private:
   
    unsigned int highLimit;
};

MOCKCPP_NS_END

#endif

