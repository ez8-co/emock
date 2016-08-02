
#include <mockcpp/IsAnything.h>
#include <mockcpp/TypelessConstraintAdapter.h>

MOCKCPP_NS_START

Constraint* any()
{
    return new TypelessConstraintAdapter(new IsAnything);
}

bool isAnyConstraint(Constraint* c)
{
    if(c == 0) return true;

    TypelessConstraintAdapter* tc = dynamic_cast<TypelessConstraintAdapter*>(c);

    return (tc != 0) && (dynamic_cast<IsAnything*>(tc->getAdaptedConstraint()) != 0);
}

MOCKCPP_NS_END

