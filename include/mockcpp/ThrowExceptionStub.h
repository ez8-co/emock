
#ifndef __MOCKCPP_THROW_EXCEPTION_STUB_H
#define __MOCKCPP_THROW_EXCEPTION_STUB_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/TypelessStub.h>
#include <mockcpp/Formatter.h>
#include <mockcpp/OutputStringStream.h>

MOCKCPP_NS_START

template <typename T>
struct ThrowExceptionStub : public TypelessStub
{
    ThrowExceptionStub(T ex)
       : excep(ex), hasBeenInvoked(false)
    {}

    bool isCompleted() const
    {
        return hasBeenInvoked;
    }

    Any& invoke(void)
    {
       hasBeenInvoked = true;

       throw excep;

       return getEmptyAny();
    }

    std::string toString(void) const
    {
       oss_t oss;

       oss << "throws(" << MOCKCPP_NS::toString(excep) << ")";

       return oss.str();
    }

    const std::type_info& type() const
    {
        return typeid(T);
    }

private:

    bool hasBeenInvoked;
 
    T excep;
};

MOCKCPP_NS_END

#endif

