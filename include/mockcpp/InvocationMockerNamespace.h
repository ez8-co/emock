
#ifndef __MOCKCPP_INVOCATION_MOCKER_NAMESPACE_H
#define __MOCKCPP_INVOCATION_MOCKER_NAMESPACE_H

#include <mockcpp/mockcpp.h>

#include <mockcpp/ObjNameGetter.h>

MOCKCPP_NS_START

struct InvocationMocker;

struct InvocationMockerNamespace
    : public ObjectNameGetter
{
   virtual InvocationMocker* getInvocationMocker(const std::string& id) const = 0;

   virtual ~InvocationMockerNamespace() {}
};

MOCKCPP_NS_END

#endif

