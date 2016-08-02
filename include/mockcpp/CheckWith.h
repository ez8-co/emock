
#ifndef __MOCKCPP_CHECK_WITH_H
#define __MOCKCPP_CHECK_WITH_H

#include <mockcpp/types/AnyCast.h>
#include <mockcpp/Constraint.h>
#include <mockcpp/Formatter.h>

MOCKCPP_NS_START

template <typename T, typename Predict>
struct CheckWith : public Constraint
{
    CheckWith(Predict pred)
      : predict(pred)
    {}    

    bool eval(const RefAny& val) const
    {
      if(!any_castable<T>(val)) return false;
      
      return predict(any_cast<T>(val));
    }

    std::string toString() const
    {
      return std::string("check(") + 
             MOCKCPP_NS::toTypeAndValueString(predict) +
             std::string(")");
    }

private:

    mutable Predict predict;
};

MOCKCPP_NS_END

#endif
