
#ifndef __MOCKCPP_INVOCATION_WITH_RETURN_TYPE_H
#define __MOCKCPP_INVOCATION_WITH_RETURN_TYPE_H

#include <mockcpp/mockcpp.h>

#include <mockcpp/Invocation.h>

MOCKCPP_NS_START

template <typename RT>
struct InvocationWithReturnType : public Invocation
{
	InvocationWithReturnType(
               const RefAny& p1 = RefAny()
             , const RefAny& p2 = RefAny()
             , const RefAny& p3 = RefAny()
             , const RefAny& p4 = RefAny()
             , const RefAny& p5 = RefAny()
             , const RefAny& p6 = RefAny())
		: Invocation(p1, p2, p3, p4, p5, p6)
	{}

   std::string toString(void) const;

	bool matches(Stub* stub) const
	{
      return stub->type() == typeid(RT);
	}
};

MOCKCPP_NS_END

#endif

