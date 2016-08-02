
#ifndef __MOCKCPP_TYPELESS_STUB_H
#define __MOCKCPP_TYPELESS_STUB_H

#include <string>
#include <mockcpp/mockcpp.h>
#include <mockcpp/types/Any.h>

MOCKCPP_NS_START

struct Any;

struct TypelessStub
{
    virtual bool isCompleted() const = 0;
    virtual Any& invoke(void) = 0;
    virtual std::string toString(void) const = 0;

    virtual ~TypelessStub() {}
};

MOCKCPP_NS_END

#endif

