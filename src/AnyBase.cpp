
#include <mockcpp/types/AnyBase.h>
#include <mockcpp/types/Holder.h>

MOCKCPP_NS_START

AnyBase::AnyBase() : content(0)
{}

AnyBase::AnyBase(PlaceHolder* holder)
    : content(holder)
{
}

AnyBase::~AnyBase()
{
   delete content;
}

bool AnyBase::empty() const
{
   return !content;
}

const std::type_info& AnyBase::type() const
{
   return content ? content->type() : typeid(void);
}

std::string AnyBase::toString() const
{
   return (content==0 ? std::string("void") : content->toString());
}

std::string AnyBase::toTypeString() const
{
   return (content==0 ? std::string("void") : content->toTypeString());
}

std::string AnyBase::toTypeAndValueString() const
{
   return (content==0 ? std::string("void") : content->toTypeAndValueString());
}

AnyBase& AnyBase::swap(AnyBase& rhs)
{
   PlaceHolder* temp = content;
   content = rhs.content;
   rhs.content = temp;
   return *this;
}

PlaceHolder* AnyBase::getContent() const
{
   return content;
}

MOCKCPP_NS_END

