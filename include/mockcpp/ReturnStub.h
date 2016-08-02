
#ifndef __MOCKCPP_RETURN_STUB_H
#define __MOCKCPP_RETURN_STUB_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/TypelessStub.h>

MOCKCPP_NS_START

struct ReturnStub : public TypelessStub
{
    ReturnStub(const Any& value);

    bool isCompleted() const;

    Any& invoke(void);

    std::string toString(void) const;

    const std::type_info& type() const;

private:
    Any returnValue;
    bool hasBeenInvoked;

};

MOCKCPP_NS_END

#endif

