
#include <mockcpp/OutputStringStream.h>
#include <mockcpp/DecoratedConstraint.h>

MOCKCPP_NS_START

/////////////////////////////////////////////////////////////////////
DecoratedConstraint::DecoratedConstraint(Constraint* constraint)
      : decoratedConstraint(constraint)
{}

/////////////////////////////////////////////////////////////////////
DecoratedConstraint::~DecoratedConstraint()
{
    delete decoratedConstraint;
}

/////////////////////////////////////////////////////////////////////
bool DecoratedConstraint::eval(const RefAny& val) const
{
    if (hasDecoratedConstraint() && !decoratedConstraint->eval(val))
    {
      return false;
    }

    return evalSelf(val);
}

/////////////////////////////////////////////////////////////////////
std::string DecoratedConstraint::getDecoratedConstraintString() const
{
    return hasDecoratedConstraint() ? 
           std::string(", ") + decoratedConstraint->toString() : "";
}
    
/////////////////////////////////////////////////////////////////////
bool DecoratedConstraint::hasDecoratedConstraint() const
{
    return decoratedConstraint != 0;
}

/////////////////////////////////////////////////////////////////////
std::string DecoratedConstraint::toString() const
{
    oss_t oss;

    oss << getName() << "(" << getTypeAndValueString()
        << getDecoratedConstraintString() << ")";

    return oss.str();
}


MOCKCPP_NS_END


