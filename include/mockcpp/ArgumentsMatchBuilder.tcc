
#include <mockcpp/InvocationMocker.h>
#include <mockcpp/Constraint.h>
#include <mockcpp/ConstraintSet.h>
#include <mockcpp/types/Any.h>

MOCKCPP_NS_START

template <typename Builder>
Builder& 
ArgumentsMatchBuilder<Builder>::
with( const Any& c01 
    , const Any& c02 
    , const Any& c03
    , const Any& c04 
    , const Any& c05
    , const Any& c06 
    , const Any& c07 
    , const Any& c08 
    , const Any& c09 
    , const Any& c10 
    , const Any& c11 
    , const Any& c12 
)
{
    getMocker()->addMatcher(
      new ConstraintSet( c01.getConstraint()
                       , c02.getConstraint()
                       , c03.getConstraint()
                       , c04.getConstraint()
                       , c05.getConstraint()
                       , c06.getConstraint()
                       , c07.getConstraint()
                       , c08.getConstraint()
                       , c09.getConstraint()
                       , c10.getConstraint()
                       , c11.getConstraint()
                       , c12.getConstraint()));
    return *this;
}

template <typename Builder>
Builder&
ArgumentsMatchBuilder<Builder>::
which(unsigned int which1, const Any& c)
{
    getMocker()->addMatcher(new ConstraintSet(which1, c.getConstraint()));
    return *this;
}

#if 0
template <typename Builder>
Builder&
ArgumentsMatchBuilder<Builder>::
with( Constraint* c01 
    , Constraint* c02
    , Constraint* c03
    , Constraint* c04
    , Constraint* c05
    , Constraint* c06
    , Constraint* c07
    , Constraint* c08
    , Constraint* c09
    , Constraint* c10
    , Constraint* c11
    , Constraint* c12
)
{
    getMocker()->addMatcher(
      new ConstraintSet(c01, c02, c03, c04, c05, c06,
                        c07, c08, c09, c10, c11, c12));
    return *this;
}

#endif

MOCKCPP_NS_END


