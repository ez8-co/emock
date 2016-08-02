
#ifndef __MOCKPP_REFHOLDER_H
#define __MOCKPP_REFHOLDER_H

#include <mockcpp/types/Holder.h>

MOCKCPP_NS_START

template<typename ValueType>
struct RefHolder : public Holder<ValueType>
{
    RefHolder(const ValueType& value)
      : ref(value)
    {
    }

    PlaceHolder * clone() const
    { return new RefHolder(ref); }

    const ValueType& getValue() const
    {
      return ref;
    }

    void changeValue(const ValueType& val)
    {
      ValueType* addr = &const_cast<ValueType&>(ref);
      (*addr) = val;
    }

private:

    const ValueType& ref;
};

MOCKCPP_NS_END


#endif // __MOCKPP_REFHOLDER_H


