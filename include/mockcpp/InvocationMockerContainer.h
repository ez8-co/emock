
#ifndef __MOCKPP_INVOCATION_MOCKER_CONTAINER_H
#define __MOCKPP_INVOCATION_MOCKER_CONTAINER_H

#include <mockcpp/mockcpp.h>

#include <string>

MOCKCPP_NS_START

struct InvocationMocker;

struct InvocationMockerContainer
{
   virtual void addInvocationMocker(InvocationMocker* mocker) = 0;
   virtual void addDefaultInvocationMocker(InvocationMocker* mocker) = 0;
   virtual InvocationMocker* getInvocationMocker(const std::string& id) = 0;

   virtual ~InvocationMockerContainer() {}
};


MOCKCPP_NS_END


#endif 

