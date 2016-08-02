
#include <mockcpp/mockcpp.h>

#include <mockcpp/types/Any.h>

MOCKCPP_NS_START

Any::Any() {}

#if 0
Any::Any(const char* value)
   : AnyBase(new ValueHolder<const char*>(value))
{
}
#endif

Any::Any(const Any & other)
   : AnyBase(other.getContent() ? other.getContent()->clone() : 0)
{
}

Any& Any::operator=(const Any & rhs)
{
   Any(rhs).swap(*this);
   return *this;
}

/////////////////////////////////////////////////////////////////
Any& getEmptyAny()
{
    return const_cast<Any&>(EmptyAny);
}

Any& getVoidAny()
{
    return const_cast<Any&>(VoidAny);
}

bool isVoidAny(const Any& val)
{
    return val.type() == VoidAny.type();
}

/////////////////////////////////////////////////////////////////

MOCKCPP_NS_END


