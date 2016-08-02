
#include <mockcpp/types/RefAny.h>

MOCKCPP_NS_START

RefAny::RefAny() {}

#if 0
RefAny::RefAny(const char* value)
      : AnyBase(new RefHolder<const char*>(value))
{
}

RefAny::RefAny(char* value)
      : AnyBase(new RefHolder<char*>(value))
{
}

#endif

RefAny::RefAny(const RefAny & other)
      : AnyBase(other.getContent() ? other.getContent()->clone() : 0)
{
}

RefAny& RefAny::operator=(const RefAny & rhs)
{
   RefAny(rhs).swap(*this);
   return *this;
}

RefAny& getEmptyRefAny()
{
    return const_cast<RefAny&>(EmptyRefAny);
}
/////////////////////////////////////////////////////

MOCKCPP_NS_END

