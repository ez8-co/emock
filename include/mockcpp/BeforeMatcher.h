
#ifndef __MOCKCPP_BEFORE_MATCHER_H
#define __MOCKCPP_BEFORE_MATCHER_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/OrderingMatcher.h>

#include <string>

MOCKCPP_NS_START

struct InvocationMocker;
struct Invocation;

struct BeforeMatcher : public OrderingMatcher
{
   BeforeMatcher();

   bool matches(const Invocation& inv) const;

   void increaseInvoked(const Invocation& inv);

   std::string toString() const;

   void verify();

   bool isCompleted(void) const;

   void setOrderingInvocationMocker(InvocationMocker* mocker);

private:

   InvocationMocker* previousCall;
};

MOCKCPP_NS_END

#endif

