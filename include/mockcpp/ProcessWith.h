
#ifndef __MOCKCPP_PROCESS_WITH_H
#define __MOCKCPP_PROCESS_WITH_H

#include <mockcpp/types/AnyCast.h>
#include <mockcpp/Constraint.h>
#include <mockcpp/Formatter.h>

MOCKCPP_NS_START

template <typename T, typename Proc>
struct ProcessWith: public Constraint
{
    ProcessWith(Proc proc)
      : proc(proc)
    {}    

    bool eval(const RefAny& val) const
    {
      if(!any_castable<T>(val)) return false;
      
      proc(any_cast<T>(val));

      return true;
    }

    std::string toString() const
    {
      return std::string("operate(") + 
             MOCKCPP_NS::toTypeAndValueString(proc) +
             std::string(")");
    }

private:

    mutable Proc proc;
};

MOCKCPP_NS_END

#endif
