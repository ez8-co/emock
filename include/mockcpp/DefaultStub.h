
#ifndef __MOCKCPP_DEFAULT_STUB_H
#define __MOCKCPP_DEFAULT_STUB_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/Stub.h>

MOCKCPP_NS_START

struct Any;
struct Invocation;

struct DefaultStub : public Stub
{
    DefaultStub(Stub* stub);

    ~DefaultStub();

    Any& invoke(const Invocation& inv);
    
    std::string toString() const;

private:

    Stub* defaultStub;   
};

MOCKCPP_NS_END

#endif

