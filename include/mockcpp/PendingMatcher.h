
#ifndef __MOCKCPP_PENDING_MATCHER_H
#define __MOCKCPP_PENDING_MATCHER_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/Matcher.h>

#include <string>

MOCKCPP_NS_START

struct Invocation;
struct OrderingMatcher;
struct InvocationMockerNamespace;
struct InvocationMocker;

struct PendingMatcher : public Matcher
{
   PendingMatcher(OrderingMatcher* orderingMatcher
                 , InvocationMockerNamespace* ns
                 , const std::string& identity
                 , InvocationMocker* ThisMocker);

	~PendingMatcher();

	bool matches(const Invocation& inv) const;

	void increaseInvoked(const Invocation& inv);

	std::string toString() const;

	void verify();

private:

	void setUpOrderingMatcher() const;

private:

   mutable OrderingMatcher* matcher;
	InvocationMockerNamespace* scope;
   std::string id;
   InvocationMocker* mocker;
};

MOCKCPP_NS_END

#endif

