
#ifndef __MOCKCPP_INVOCATION_MOCKER_H
#define __MOCKCPP_INVOCATION_MOCKER_H

#include <mockcpp/mockcpp.h>

#include <mockcpp/SelfDescribe.h>

MOCKCPP_NS_START

struct Method;
struct Matcher;
struct Stub;
struct InvocationMockerImpl;
struct Invocation;
struct InvocationId;
struct Any;

struct InvocationMocker : public SelfDescribe
{
    InvocationMocker(Method* core);
    ~InvocationMocker();

    Method* getMethod() const;
    void addStub(Stub* stub);
    void addMatcher(Matcher* matcher);
    bool hasBeenInvoked(void) const ;

    void setId(InvocationId* id);
    const InvocationId* const getId(void) const;

    bool matches(const Invocation& inv) const;
    Any& invoke(const Invocation& inv);

    void verify();

    std::string toString() const;

private:
    InvocationMockerImpl* This;
};

MOCKCPP_NS_END

#endif

