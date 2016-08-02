
#ifndef __MOCKCPP_DIE_STUB_H
#define __MOCKCPP_DIE_STUB_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/TypelessStub.h>

MOCKCPP_NS_START

struct DieStub : public TypelessStub
{
    DieStub(int exitCode = 0);

    bool isCompleted() const;

    Any& invoke(void);

    std::string toString(void) const;

    const std::type_info& type() const;

private:

    int code;
};

MOCKCPP_NS_END

#endif

