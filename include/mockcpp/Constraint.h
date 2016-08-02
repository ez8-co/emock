
#ifndef __MOCKCPP_CONSTRAINT_H
#define __MOCKCPP_CONSTRAINT_H

#include <string>
#include <mockcpp/types/RefAny.h>

MOCKCPP_NS_START

struct RefAny;

struct Constraint
{
    virtual ~Constraint() {}

    virtual bool eval(const RefAny& inv) const = 0;
    virtual std::string toString() const = 0;
};

MOCKCPP_NS_END

#endif

