
#ifndef __MOCKCPP_CONSTRAINT_SET_H
#define __MOCKCPP_CONSTRAINT_SET_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/StatelessMatcher.h>
#include <mockcpp/IsAnythingHelper.h>

MOCKCPP_NS_START

struct Invocation;
struct Constraint;
struct ConstraintSetImpl;

struct ConstraintSet: public StatelessMatcher
{
    ConstraintSet(unsigned int which, Constraint* p);

    ConstraintSet( Constraint* p01 = any()
                 , Constraint* p02 = any()
                 , Constraint* p03 = any()
                 , Constraint* p04 = any()
                 , Constraint* p05 = any()
                 , Constraint* p06 = any()
                 , Constraint* p07 = any()
                 , Constraint* p08 = any()
                 , Constraint* p09 = any()
                 , Constraint* p10 = any()
                 , Constraint* p11 = any()
                 , Constraint* p12 = any()
    );

    ~ConstraintSet();

    virtual bool matches(const Invocation& inv) const;

    virtual std::string toString() const;

    virtual void verify(void);

private:

    ConstraintSetImpl* This;
};

MOCKCPP_NS_END

#endif

