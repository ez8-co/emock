
#ifndef __MOCKPP_ANY_H
#define __MOCKPP_ANY_H

#include <mockcpp/types/AnyBase.h>

#include <mockcpp/types/ValueHolder.h>
#include <mockcpp/Void.h>

MOCKCPP_NS_START

struct Any : public AnyBase
{
   Any();

   template <typename ValueType>
   Any(const ValueType& value)
      : AnyBase(new ValueHolder<ValueType>(value))
   {}

   Any(const Any & other);

public:

   template<typename ValueType>
   Any& operator=(const ValueType & rhs)
   {
      Any(rhs).swap(*this);
      return *this;
   }

   Any& operator=(const Any & rhs);

   Constraint* getConstraint() const
   { return getContent()->getConstraint(); }
};

/////////////////////////////////////////////////////////////////
const Any EmptyAny;

const Any VoidAny = Any(Void());

Any& getEmptyAny();
Any& getVoidAny();
bool isVoidAny(const Any& val);

/////////////////////////////////////////////////////////////////

MOCKCPP_NS_END


#endif // __MOCKPP_ANY_H


