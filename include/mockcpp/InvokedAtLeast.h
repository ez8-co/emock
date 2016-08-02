
#ifndef __MOCKCPP_INVOKED_ATLEAST_H
#define __MOCKCPP_INVOKED_ATLEAST_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/InvocationTimesMatcher.h>

MOCKCPP_NS_START

struct InvokedAtLeast : public InvocationTimesMatcher
{
    InvokedAtLeast(const unsigned int times);

    bool matches(const Invocation& inv) const;

    void verify(void);

    std::string toString() const;

private:
   
    unsigned int lowLimit;
};

MOCKCPP_NS_END

#endif

