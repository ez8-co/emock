
#include <mockcpp/TypelessStubAdapter.h>
#include <mockcpp/TypelessStub.h>

MOCKCPP_NS_START

////////////////////////////////////////////////////////
TypelessStubAdapter::TypelessStubAdapter(TypelessStub* ts)
		: stub(ts)
{}

////////////////////////////////////////////////////////
TypelessStubAdapter::~TypelessStubAdapter()
{
	delete stub;
}

bool TypelessStubAdapter::isCompleted() const
{
   return stub->isCompleted();
}
////////////////////////////////////////////////////////
Any& TypelessStubAdapter::invoke(const Invocation& inv)
{
	return stub->invoke();
}

////////////////////////////////////////////////////////
std::string TypelessStubAdapter::toString() const
{
   return stub->toString();
}

////////////////////////////////////////////////////////

MOCKCPP_NS_END


