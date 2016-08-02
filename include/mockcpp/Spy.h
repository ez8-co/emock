
#ifndef __MOCKCPP_SPY_H
#define __MOCKCPP_SPY_H

#include <string>
#include <mockcpp/types/RefAny.h>

MOCKCPP_NS_START

struct RefAny;

template <typename T>
struct Spy : public Constraint
{
    Spy(T& reference)
       : ref(reference)
    {}

    bool eval(const RefAny& inv) const
    {
         if(!any_castable<T>(inv)) return false;
         ref = any_cast<T>(inv);
         return true;
    }

    std::string toString() const
    {
        return "spy(" + toTypeAndValueString(ref) + ")";
    }

private:
    T& ref;
};

MOCKCPP_NS_END

#endif

