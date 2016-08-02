
#ifndef __MOCKCPP_INVOKED_EXACTLY_H
#define __MOCKCPP_INVOKED_EXACTLY_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/InvocationTimesMatcher.h>

MOCKCPP_NS_START

struct InvokedExactly : public InvocationTimesMatcher
{
    InvokedExactly(const unsigned int times);

    bool matches(const Invocation& inv) const;

    void verify(void);

    std::string toString(void) const;

private:
   
    unsigned int expectedInvokedTimes;
};

MOCKCPP_NS_END

#endif

