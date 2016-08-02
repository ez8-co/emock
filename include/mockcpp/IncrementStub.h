
#ifndef __MOCKCPP_INCREAMENT_STUB_H
#define __MOCKCPP_INCREAMENT_STUB_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/TypelessStub.h>
#include <mockcpp/Formatter.h>
#include <mockcpp/OutputStringStream.h>
#include <mockcpp/Asserter.h>

MOCKCPP_NS_START

template <typename T>
struct IncrementStub : public TypelessStub
{
    IncrementStub(T startValue, T endValue)
       : from(startValue), to(endValue), current(startValue), hasEnd(true)
    {}

    IncrementStub(T startValue)
       : from(startValue), current(startValue), hasEnd(false)
    {}

    bool isCompleted() const
    {
       if(!hasEnd) 
       {
           return false;
       }

       return current > to; 
    }

    Any& invoke(void)
    {
       checkEnd();
       value = Any(current);
       current++;
       return value;
    }

    std::string toString(void) const
    {
       oss_t oss;

       oss << "increase(" << from;

       if(hasEnd)
       {
         oss << " ," << to;
       }

       oss << ")";

       return oss.str();
    }

    const std::type_info& type() const
    {
        return typeid(T);
    }

private:

   void checkEnd()
   {
      if(!hasEnd)
      {
         return;
      }
      oss_t oss;
      oss << "Returned value has increased to specified end value"
            << "(" << to << ")";
      MOCKCPP_ASSERT_TRUE_MESSAGE(
           oss.str(),
           current <= to);
   }

private:

    Any value;

    bool hasEnd;

    T current;
    T from;
    T to;
};

MOCKCPP_NS_END

#endif

