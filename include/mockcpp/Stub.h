
#ifndef __MOCKCPP_STUB_H
#define __MOCKCPP_STUB_H

#include <mockcpp/types/Any.h>

#include <mockcpp/SelfDescribe.h>

MOCKCPP_NS_START

struct Any;
struct Invocation;

struct Stub : public SelfDescribe
{
    virtual ~Stub() {}
    virtual bool isCompleted() const = 0;
    virtual Any& invoke(const Invocation& inv) = 0;
};

MOCKCPP_NS_END

#endif

