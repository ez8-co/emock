
#ifndef __MOCKCPP_ORDERING_MATCHER_H
#define __MOCKCPP_ORDERING_MATCHER_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/Matcher.h>

MOCKCPP_NS_START

struct InvocationMocker;

struct OrderingMatcher : public Matcher
{
   virtual ~OrderingMatcher() {}
   virtual bool isCompleted(void) const = 0;
   virtual void setOrderingInvocationMocker(InvocationMocker* mocker) = 0;
};

MOCKCPP_NS_END

#endif

