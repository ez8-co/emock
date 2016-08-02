
#ifndef __MOCKCPP_THEN_STUB_H
#define __MOCKCPP_THEN_STUB_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/Stub.h>

MOCKCPP_NS_START

struct Any;
struct Invocation;

struct ThenStub : public Stub
{
    ThenStub(Stub* stub);

    ~ThenStub();

    bool isCompleted(void) const;
    Any& invoke(const Invocation& inv);
    
    std::string toString() const;

private:

    Stub* expectedStub; 
};

MOCKCPP_NS_END

#endif

