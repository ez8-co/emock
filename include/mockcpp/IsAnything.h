
#ifndef __MOCKCPP_IS_ANYTHING_H
#define __MOCKCPP_IS_ANYTHING_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/TypelessConstraint.h>

MOCKCPP_NS_START

struct IsAnything : public TypelessConstraint
{
    virtual bool eval(void) const
    { return true; }

    virtual std::string toString() const
    {
      return std::string("any()");
    }
};


MOCKCPP_NS_END

#endif

