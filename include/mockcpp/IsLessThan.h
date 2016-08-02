
#ifndef __MOCKCPP_IS_LESS_THAN_H
#define __MOCKCPP_IS_LESS_THAN_H

#include <mockcpp/types/AnyCast.h>
#include <mockcpp/Constraint.h>
#include <mockcpp/Formatter.h>

MOCKCPP_NS_START

template <typename T>
struct IsLessThan : public Constraint
{
    IsLessThan(const T& expected)
      : expectedValue(expected)
    {}

    ~IsLessThan() {}

    bool eval(const RefAny& val) const
    {
      if(!any_castable<T>(val)) return false;
      return any_cast<T>(val) < expectedValue;
    }

    std::string toString() const
    {
      return std::string("lt(") + 
             MOCKCPP_NS::toTypeAndValueString(expectedValue) +
             std::string(")");
    }

private:

    T expectedValue;
};

MOCKCPP_NS_END

#endif

