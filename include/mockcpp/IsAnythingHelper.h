
#ifndef __MOCKCPP_IS_ANYTHING_HELPER_H
#define __MOCKCPP_IS_ANYTHING_HELPER_H

#include <mockcpp/mockcpp.h>

MOCKCPP_NS_START

struct Constraint;

Constraint* any();

static const Constraint* _ = 0;

bool isAnyConstraint(Constraint* c);

MOCKCPP_NS_END

#endif

