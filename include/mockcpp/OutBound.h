
#ifndef __MOCKCPP_OUTBOUND_H
#define __MOCKCPP_OUTBOUND_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/DecoratedConstraint.h>
#include <mockcpp/Formatter.h>
#include <mockcpp/Asserter.h>
#include <mockcpp/IsRef.h>

MOCKCPP_NS_START

template <typename T>
struct OutBound : public DecoratedConstraint
{
    OutBound(const T& val, Constraint* constraint = 0)
      : ref(val), DecoratedConstraint(constraint)
    {}

    bool evalSelf(const RefAny& val) const
    {
      return const_cast<RefAny&>(val).changeValue(ref);
    }

    std::string getName() const
    {
      return "outBound";
    }

    std::string getTypeAndValueString() const
    {
      return MOCKCPP_NS::toTypeAndValueString(ref);
    }

private:

    T ref;
};

MOCKCPP_NS_END

#endif

