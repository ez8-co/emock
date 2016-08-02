
#include <mockcpp/TypelessConstraintAdapter.h>
#include <mockcpp/TypelessConstraint.h>

MOCKCPP_NS_START

//////////////////////////////////////////////////////////////////////////
struct TypelessConstraintAdapterImpl
{
   TypelessConstraint* typelessConstraint;

   TypelessConstraintAdapterImpl(TypelessConstraint* c)
		: typelessConstraint(c)
   {}

   ~TypelessConstraintAdapterImpl()
	{
		delete typelessConstraint;
	}
};

//////////////////////////////////////////////////////////////////////////
TypelessConstraintAdapter::TypelessConstraintAdapter(TypelessConstraint* tc)
	: This(new TypelessConstraintAdapterImpl(tc))
{
}

//////////////////////////////////////////////////////////////////////////
TypelessConstraintAdapter::~TypelessConstraintAdapter()
{
    delete This;
}

//////////////////////////////////////////////////////////////////////////
bool
TypelessConstraintAdapter::eval(const RefAny& p) const
{
    return This->typelessConstraint->eval();
}

//////////////////////////////////////////////////////////////////////////
TypelessConstraint*
TypelessConstraintAdapter::getAdaptedConstraint() const
{
	return This->typelessConstraint;
}
//////////////////////////////////////////////////////////////////////////
std::string TypelessConstraintAdapter::toString() const
{
	return This->typelessConstraint->toString();
}

MOCKCPP_NS_END

