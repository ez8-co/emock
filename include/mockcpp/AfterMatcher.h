
#ifndef __MOCKCPP_AFTER_MATCHER_H
#define __MOCKCPP_AFTER_MATCHER_H

#include <string>

#include <mockcpp/mockcpp.h>
#include <mockcpp/OrderingMatcher.h>

MOCKCPP_NS_START

struct InvocationMocker;
struct Invocation;

struct AfterMatcher : public OrderingMatcher
{
   AfterMatcher();

   bool matches(const Invocation& inv) const;

   void increaseInvoked(const Invocation& inv);

   std::string toString() const;
   
   void verify(void);

   bool isCompleted(void) const;

   void setOrderingInvocationMocker(InvocationMocker* mocker);

private:

   InvocationMocker* previousCall;
};

MOCKCPP_NS_END

#endif

