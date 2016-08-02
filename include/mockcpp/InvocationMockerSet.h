
#ifndef __MOCKCPP_INVOCATION_MOCKER_SET_H
#define __MOCKCPP_INVOCATION_MOCKER_SET_H

#include <mockcpp/mockcpp.h>

#include <string>
#include <list>

MOCKCPP_NS_START

struct InvocationMocker;
struct Invocation;
struct SelfDescribe;
struct Any;

//////////////////////////////////////////////////////////
struct InvocationMockerSet
{
private:
    typedef std::list<InvocationMocker*> List;
    typedef List::iterator Iterator;
    typedef List::const_iterator ConstIterator;

public:
    InvocationMocker* getInvocationMocker(const std::string& id) const;
    void addInvocationMocker(InvocationMocker* mocker);

    void reset();
    void verify();

    const Any& invoke(const Invocation& inv, SelfDescribe* &resultProvider);

    std::string toString() const;

private:

    List mockers;
};

MOCKCPP_NS_END

#endif

